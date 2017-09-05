//
// Created on 2017/09/03 at 17:27.
//

#include <QtCore/QDateTime>
#include "GameController.hpp"

#include "../Models/Containers/CardContainer.hpp"
#include "../Models/Card/Unit.hpp"
#include "../Models/Card/Effect.hpp"
#include "../Models/Meta/UnitMeta.hpp"
#include "../Models/Meta/EffectsMeta.hpp"


void GameController::DeployUnitToBattleLine(int cardId, const QString& battleLineName, int index)
{
    _battleField->GetBattleLineByName(battleLineName)->InsertUnit(cardId, index);
    _cardManager->GetCardById(cardId)->OnDeploy();
}


bool GameController::IsThisUnitEnemy(int id)
{
    return _battleField->GetBattleLineContainingCard(id).startsWith("Enemy");
}


bool GameController::IsThisUnitAllied(int id)
{
    return _battleField->GetBattleLineContainingCard(id).startsWith("Allied");
}


void GameController::SetWeatherToBattleLine(const QString& battleLineName, BattleLine::WeatherEnum weather)
{
    _battleField->GetBattleLineByName(battleLineName)->SetWeather(weather);
}


bool GameController::DeployCardFromContainerToBattleLine
    (const QString& cardName, const QString& containerName, const QString& battleLineName, int index)
{
    auto container = _battleField->GetCardContainerByName(containerName);

    for (auto& j:container->GetCards())
    {
        if (_cardManager->GetCardById(j)->GetCardMetaInfo()->GetName() == cardName)
        {
            container->RemoveCardOfId(j);
            DeployUnitToBattleLine(j, battleLineName, index);
            return true;
        }
    }

    return false;
}


BattleField *GameController::GetBattleField() const
{
    return _battleField;
}


CardManager *GameController::GetCardManager() const
{
    return _cardManager;
}


//<editor-fold desc="special rules">

void GameController::HandleImpenetrableFogDeployed(const QString& battleLine)
{
    auto fogletDeployLine = battleLine;
    if (fogletDeployLine.startsWith("Enemy"))
    {
        fogletDeployLine.replace(0, 5, "Allied");
    }

    // todo Maybe the location should be selected by player? Place to rightmost place now.
    int index = GetBattleField()->GetBattleLineByName(fogletDeployLine)->GetUnits().size();

    auto success = DeployCardFromContainerToBattleLine("Foglet", "AlliedDeck", fogletDeployLine, index);

    if (!success)
    {
        DeployCardFromContainerToBattleLine("Foglet", "AlliedGrave", fogletDeployLine, index);
    }
}


void GameController::HandleGoldCardDeploying()
{
    qsrand(static_cast<uint>(QDateTime::currentMSecsSinceEpoch()));
    auto lineNumber = qrand() % 3;
    auto lineName   = QVector<QString>({QString("AlliedSiege"),
                                        QString("AlliedRanged"),
                                        QString("AlliedMelee")})[lineNumber];

    auto size  = _battleField->GetBattleLineByName(lineName)->GetUnits().size();
    auto index = qrand() % (size + 1);

    DeployCardFromContainerToBattleLine("Roach", "AlliedDeck", lineName, index);
}


int GameController::GetPowerUpOfSwallowing(int swallowedCardId)
{
    auto unit  = dynamic_cast<Unit *>(_cardManager->GetCardById(swallowedCardId));
    auto power = unit->GetPower();

    if (unit->GetCardMetaInfo()->GetName() == "HarpyEgg")
    {
        power += 5;
    }

    return power;
}


void GameController::HandleUnitSwallowed()
{
    for (const auto& lineName:QVector<QString>({QString("Melee"), QString("Ranged"), QString("Siege")}))
    {
        auto battleLineName = "Allied" + lineName;

        for (const auto item:_battleField->GetBattleLineByName(battleLineName)->GetUnits())
        {
            if (_cardManager->GetCardById(item)->GetCardMetaInfo()->GetName() == "ArachasBehemoth")
            {
                dynamic_cast<Unit *>(_cardManager->GetCardById(item))->DamageIgnoringArmorAndShield(1);

                // deploy arachas hatchling
                auto arachasHatchling = CardMeta::GetMetaByCardName("ArachasHatchling");
                Interacting->GetSelectedCardFromSpanningCards(QVector<CardMeta *>({arachasHatchling}));
                delete arachasHatchling;

                auto id = SpawnCard("ArachasHatchling", "AlliedHand", 0);
                DeployTheCardOfId(id);
            }
        }
    }
}

//</editor-fold>


int GameController::GetNextId()
{
    static int currentId = 0;
    currentId++;
    return currentId;
}


int GameController::SpawnCard(const QString& cardName, const QString& containerOrBattleLineName, int index)
{
    auto card = Card::SpanCardByName(cardName);
    card->SetCardId(GetNextId());
    _cardManager->RegisterCard(card);

    if (BattleField::IsABattleLine(containerOrBattleLineName))
    {
        if (index == -1)
        {
            auto size = _battleField->GetBattleLineByName(containerOrBattleLineName)->GetUnits().size();
            qsrand(static_cast<uint>(QDateTime::currentMSecsSinceEpoch()));
            index = qrand() % (size + 1);
        }

        _battleField->GetBattleLineByName(containerOrBattleLineName)->InsertUnit(card->GetCardId(), index);
    }
    else if (BattleField::IsAContainer(containerOrBattleLineName))
    {
        if (index == -1)
        {
            auto size = _battleField->GetCardContainerByName(containerOrBattleLineName)->GetCards().size();
            qsrand(static_cast<uint>(QDateTime::currentMSecsSinceEpoch()));
            index = qrand() % (size + 1);
        }

        _battleField->GetCardContainerByName(containerOrBattleLineName)->InsertCard(card->GetCardId(), index);
    }

    return card->GetCardId();
}


bool GameController::MoveCardFromBattleLineToBattleLine
    (int id, const QString& sourceBattleLineName, const QString& destinationBattleLineName, int index)
{
    try
    {
        auto sourceBattleLine = _battleField->GetBattleLineByName(sourceBattleLineName);
        sourceBattleLine->RemoveCardOfId(id);
        auto destinationBattleLine = _battleField->GetBattleLineByName(destinationBattleLineName);
        destinationBattleLine->InsertUnit(id, index);
        return true;
    }
    catch (...)
    {
        return false;
    }
}


InteractingController *GameController::GetInteracting() const
{
    return Interacting;
}


void GameController::SetInteracting(InteractingController *Interacting)
{
    GameController::Interacting = Interacting;
}


bool GameController::MoveCardFromCardsSetToCardsSet
    (int id, const QString& sourceCardsSetName, const QString& destinationCardsSetName, int index)
{
    try
    {
        if (_battleField->IsAContainer(sourceCardsSetName))
        {
            auto sourceContainer = _battleField->GetCardContainerByName(sourceCardsSetName);
            sourceContainer->RemoveCardOfId(id);
        }
        else if (_battleField->IsABattleLine(sourceCardsSetName))
        {
            auto sourceBattleLine = _battleField->GetBattleLineByName(sourceCardsSetName);
            sourceBattleLine->RemoveCardOfId(id);
        }
        else
        {
            return false;
        }

        if (_battleField->IsAContainer(destinationCardsSetName))
        {
            auto destinationContainer = _battleField->GetCardContainerByName(destinationCardsSetName);
            destinationContainer->InsertCard(id, index);
        }
        else if (_battleField->IsABattleLine(destinationCardsSetName))
        {
            auto destinationBattleLine = _battleField->GetBattleLineByName(destinationCardsSetName);
            destinationBattleLine->InsertUnit(id, index);
        }
        else
        {
            return false;
        }

        return true;
    }
    catch (...)
    {
        return false;
    }

    return false;
}


bool GameController::MoveCardFromCardsSetToCardsSet(int id, const QString& destinationCardsSetName, int index)
{
    auto battleLine = _battleField->GetBattleLineContainingCard(id);
    if (battleLine != "")
    {
        return MoveCardFromCardsSetToCardsSet(id, battleLine, destinationCardsSetName, index);
    }

    auto container = _battleField->getCardContainerContainingCard(id);
    if (container != "")
    {
        return MoveCardFromCardsSetToCardsSet(id, container, destinationCardsSetName, index);
    }

    return false;
}


// todo merge validation into cards
void GameController::DeployTheCardOfId(int id)
{
    auto card = _cardManager->GetCardById(id);

    if (Unit::IsCardUnit(card))
    {
        QString deployLine;
        int     deployIndex;
        Interacting->GetSelectedUnitDeployLocation(deployLine, deployIndex);

        auto isValid = false;

        do
        {
            QString prefix = (dynamic_cast<UnitMeta *>(card->GetCardMetaInfo())->IsLoyal()) ? "Allied" : "Enemy";

            switch (dynamic_cast<UnitMeta *>(card->GetCardMetaInfo())->GetDeployLocation())
            {
            case UnitMeta::DeployLocationEnum::Melee:
                if (deployLine != prefix + "Melee")
                {
                    continue;
                }
            case UnitMeta::DeployLocationEnum::Ranged:
                if (deployLine != prefix + "Ranged")
                {
                    continue;
                }
            case UnitMeta::DeployLocationEnum::Siege:
                if (deployLine != prefix + "Siege")
                {
                    continue;
                }
            case UnitMeta::DeployLocationEnum::Any:
            {
                MoveCardFromCardsSetToCardsSet(id, deployLine, deployIndex);
                dynamic_cast<Unit *>(card)->SetSelectedLine(deployLine);
                dynamic_cast<Unit *>(card)->SetSelectedIndex(deployIndex);
                card->OnDeploy();
                isValid = true;
                break;
            }
            }
        }
        while (!isValid);
    }
    else if (Effect::IsCardEffect(card))
    {
        switch (dynamic_cast<EffectsMeta *>(card->GetCardMetaInfo())->GetDeployType())
        {
        case EffectsMeta::DeployTypeEnum::GlobalSelection:
        {
            Interacting->GetGlobalSelection();
            break;
        }
        case EffectsMeta::DeployTypeEnum::TargetSelection:
        {
            auto targetId = Interacting->GetSelectedCardFromBattleField();
            dynamic_cast<Effect *>(card)->SetSelectedUnit(targetId);
            card->OnDeploy();
            break;
        }
        case EffectsMeta::DeployTypeEnum::LineSelect:
        {
            auto battleLine = Interacting->GetSelectedEffectDeployBattleLine();
            dynamic_cast<Effect *>(card)->SetSelectedLine(battleLine);
            card->OnDeploy();
            break;
        }
        }
    }
}


