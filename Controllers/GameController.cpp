//
// Created on 2017/09/03 at 17:27.
//

#include <QtCore/QDateTime>
#include "GameController.hpp"

#include "../Models/Containers/CardContainer.hpp"


void GameController::DeployUnitToBattleLine(int cardId, const QString& battleLineName, int index)
{
    _battleField->GetBattleLineByName(battleLineName)->InsertUnit(cardId, index);
    _cardManager->GetCardById(cardId)->OnDeploy();
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


int GameController::GetNextId()
{
    static int currentId = 0;
    currentId++;
    return currentId;
}


int GameController::SpanCard(const QString& cardName, const QString& containerOrBattleLineName, int index)
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
