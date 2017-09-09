//
// Created on 2017/09/03 at 17:27.
//

#include <QtCore/QDateTime>
#include <c++/iostream>
#include "GameController.hpp"

#include "../Models/Containers/CardContainer.hpp"
#include "../Models/Card/Unit.hpp"
#include "../Models/Card/Effect.hpp"
#include "../Models/Meta/UnitMeta.hpp"
#include "../Models/Meta/EffectsMeta.hpp"


BattleField *GameController::GetBattleField() const
{
    return _battleField;
}


CardManager *GameController::GetCardManager() const
{
    return _cardManager;
}


InteractingController *GameController::GetInteracting() const
{
    return Interacting;
}


void GameController::SetInteracting(InteractingController *Interacting)
{
    GameController::Interacting = Interacting;
}


int GameController::GetNextId()
{
    static int currentId = 0;
    currentId++;
    return currentId;
}


bool GameController::IsThisUnitEnemy(int id)
{
    return _battleField->GetBattleLineContainingCard(id).startsWith("Enemy");
}


bool GameController::IsThisUnitAllied(int id)
{
    return _battleField->GetBattleLineContainingCard(id).startsWith("Allied");
}


bool GameController::IsThisCardEnemy(int id)
{
    if (_battleField->GetBattleLineContainingCard(id) != "")
    {
        return IsThisUnitEnemy(id);
    }
    else if (_battleField->getCardContainerContainingCard(id) != "")
    {
        return _battleField->getCardContainerContainingCard(id).startsWith("Enemy");
    }

    throw 0;
}


bool GameController::IsThisCardAllied(int id)
{
    if (_battleField->GetBattleLineContainingCard(id) != "")
    {
        return IsThisUnitAllied(id);
    }
    else if (_battleField->getCardContainerContainingCard(id) != "")
    {
        return _battleField->getCardContainerContainingCard(id).startsWith("Allied");
    }

    throw 0;
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

    auto success = DeployUnitFromContainerToBattleLine("Foglet", "AlliedDeck", fogletDeployLine, index);

    if (!success)
    {
        DeployUnitFromContainerToBattleLine("Foglet", "AlliedGrave", fogletDeployLine, index);
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

    DeployUnitFromContainerToBattleLine("Roach", "AlliedDeck", lineName, index);
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


//<editor-fold desc="Cards manipulation">

void GameController::DeployUnitToBattleLine(int cardId, const QString& battleLineName, int index)
{
    auto containerName = _battleField->getCardContainerContainingCard(cardId);
    MoveCardFromCardsSetToCardsSet(cardId, containerName, battleLineName, index);
    dynamic_cast<Unit *>(_cardManager->GetCardById(cardId))->SetSelectedLine(battleLineName);
    dynamic_cast<Unit *>(_cardManager->GetCardById(cardId))->SetSelectedIndex(index);
    _cardManager->GetCardById(cardId)->OnDeploy();
}


void GameController::SetWeatherToBattleLine(const QString& battleLineName, BattleLine::WeatherEnum weather)
{
    _battleField->GetBattleLineByName(battleLineName)->SetWeather(weather);
}


bool GameController::DeployUnitFromContainerToBattleLine
    (const QString& cardName, const QString& containerName, const QString& battleLineName, int index)
{
    auto container = _battleField->GetCardContainerByName(containerName);

    for (int i = 0; i < container->GetCards().size(); i++)
    {
        auto id = container->GetCards()[i];

        if (_cardManager->GetCardById(id)->GetCardMetaInfo()->GetName() == cardName)
        {
            container->RemoveCardOfId(id);
            _battleField->GetBattleLineByName(battleLineName)->InsertUnit(id, index);
            dynamic_cast<Unit *>(_cardManager->GetCardById(id))->SetSelectedLine(battleLineName);
            dynamic_cast<Unit *>(_cardManager->GetCardById(id))->SetSelectedIndex(index);

            _cardManager->GetCardById(id)->OnDeploy();

            return true;
        }
    }

    return false;
}


int GameController::SpawnCard(const QString& cardName, const QString& containerOrBattleLineName, int index)
{
    auto card = Card::SpanCardByName(cardName, this);
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
        dynamic_cast<Unit *>(_cardManager->GetCardById(card->GetCardId()))->SetSelectedLine(containerOrBattleLineName);
        dynamic_cast<Unit *>(_cardManager->GetCardById(card->GetCardId()))->SetSelectedIndex(index);
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

        auto isValid = false;

        do
        {
            Interacting->GetSelectedUnitDeployLocation(deployLine, deployIndex);
            QString prefix = (dynamic_cast<UnitMeta *>(card->GetCardMetaInfo())->IsLoyal()) ? "Allied" : "Enemy";

            switch (dynamic_cast<UnitMeta *>(card->GetCardMetaInfo())->GetDeployLocation())
            {
            case UnitMeta::DeployLocationEnum::Melee:
                if (deployLine != prefix + "Melee")
                {
                    continue;
                }
                break;
            case UnitMeta::DeployLocationEnum::Ranged:
                if (deployLine != prefix + "Ranged")
                {
                    continue;
                }
                break;
            case UnitMeta::DeployLocationEnum::Siege:
                if (deployLine != prefix + "Siege")
                {
                    continue;
                }
                break;
            case UnitMeta::DeployLocationEnum::Any:
                if (!deployLine.startsWith(prefix))
                {
                    continue;
                }
                break;
            }

            MoveCardFromCardsSetToCardsSet(id, deployLine, deployIndex);
            dynamic_cast<Unit *>(card)->SetSelectedLine(deployLine);
            dynamic_cast<Unit *>(card)->SetSelectedIndex(deployIndex);
            card->OnDeploy();
            isValid = true;
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
            break;
        }
        case EffectsMeta::DeployTypeEnum::LineSelect:
        {
            auto battleLine = Interacting->GetSelectedEffectDeployBattleLine();
            dynamic_cast<Effect *>(card)->SetSelectedLine(battleLine);
            break;
        }
        }

        card->OnDeploy();
        card->OnDestroy();
    }

    Interacting->UpdateBattleFieldView();
}
//</editor-fold>


void GameController::StartGame()
{
    // todo remove hack
    HackBeforeStart();

    InitializeNetwork();

    std::cout << "A game is starting...\n";
    ResetGameData();

    for (int i = 0; i < 3; i++)
    {
        std::cout << "A round is starting...\n";
        InitializeRoundGameData();
        while (true)
        {
            std::cout << "Gaming loop entered...\n";

            if (!IsAllyAbdicated)
            {
                bool abdicate;
                int  cardId;

                std::cout << "Ally input <>\n";
                Interacting->GetRoundInput(abdicate, cardId);

                if (abdicate)
                {
                    IsAllyAbdicated = true;
                    std::cout << "Ally abdicate the round\n";
                }
                else
                {
                    if (!_battleField->GetCardContainerByName("AlliedHand")->IsCardContainerContainingCard(cardId))
                    {
                        break;
                    }
                    else
                    {
                        std::cout << "Ally deploying card #" << cardId << std::endl;
                        std::cout << _cardManager->GetCardById(cardId)->ToString().toStdString() << std::endl;
                        DeployTheCardOfId(cardId);
                    }
                }
            }

            if (IsAllyAbdicated && IsEnemyAbdicated)
            {
                break;
            }
        }

        if (AllyScore == 2 || EnemyScore == 2)
        {
            break;
        }
    }
}


void GameController::ResetGameData()
{
    std::cout << "Resetting game data...\n";

    IsAllyAbdicated  = false;
    IsEnemyAbdicated = false;
    AllyScore        = 0;
    EnemyScore       = 0;

    // the card group data should be ready already
    delete _battleField;
    delete _cardManager;
    delete Interacting;

    std::cout << "Initializing battle field, card manager and interacting system...\n";

    _battleField = new BattleField();
    std::cout << "Battle field initialized...\n";

    _cardManager = new CardManager();
    std::cout << "Card manager initialized...\n";

    Interacting = new InteractingController(this);
    std::cout << "Interacting controller initialized...\n";

    // index the cards
    // todo should be based on whether it is the first to start
    for (const auto& i:AllyCardGroup.GetCardMetaGroup())
    {
        auto card = Card::SpanCardByName(i.GetName(), this);
        card->SetCardId(GetNextId());
        auto id = card->GetCardId();
        _cardManager->RegisterCard(card);

        _battleField->GetCardContainerByName("AlliedDeck")->InsertCard(id, 0);
    }

    InitializeAllyCardData();
}


void GameController::InitializeRoundGameData()
{
    std::cout << "Reset round data...\n";
    IsAllyAbdicated  = false;
    IsEnemyAbdicated = false;
}


void GameController::HandleMessage(const QString& message)
{
    qDebug() << message;
}


void GameController::InitializeAllyCardData()
{
    std::cout << "Initializing card data\n";
    // shuffle the deck
    auto deck = _battleField->GetCardContainerByName("AlliedDeck")->GetCards();
    _battleField->GetCardContainerByName("AlliedDeck")->ClearCardContainer();

    std::mt19937 g(static_cast<unsigned int>(QDateTime::currentMSecsSinceEpoch()));

    std::shuffle(deck.begin(), deck.end(), g);

    // todo cheat code below
    std::cout << "[ Cheat ] Here is all your cards\n";
    for (int i : deck)
    {
        std::cout << _cardManager->GetCardById(i)->GetCardMetaInfo()->GetName().toStdString() << std::endl;
    }

    // get the leader card
    for (int i = 0; i < deck.size(); i++)
    {
        if (_cardManager->GetCardById(deck[i])->GetCardMetaInfo()->GetCardType() == CardMeta::CardTypeEnum::Leader)
        {
            auto leaderId = deck[i];
            deck.remove(i);

            // insert the leader card into hand
            _battleField->GetCardContainerByName("AlliedHand")->InsertCard(leaderId, 0);

            break;
        }
    }

    // get top-10 random cards
    for (int i = 0; i < 10; i++)
    {
        _battleField->GetCardContainerByName("AlliedHand")->InsertCard(deck[i], 1);
    }
    for (int i = 0; i < 10; i++)
    {
        deck.remove(0);
    }

    // rebuild the deck
    for (auto i:deck)
    {
        _battleField->GetCardContainerByName("AlliedDeck")->InsertCard(i, 0);
    }

    // todo cheat code below
    std::cout << "[ Cheat ] Here is all your cards in your hand:\n";
    for (const auto i:_battleField->GetCardContainerByName("AlliedHand")->GetCards())
    {
        std::cout << _cardManager->GetCardById(i)->ToString().toStdString() << std::endl;
    }
    std::cout << "[ Cheat ] Here is all your cards in your deck:\n";
    for (const auto i:_battleField->GetCardContainerByName("AlliedDeck")->GetCards())
    {
        std::cout << _cardManager->GetCardById(i)->ToString().toStdString() << std::endl;
    }
}


//<editor-fold desc="Hacking codes">
void GameController::HackBeforeStart()
{
    for (auto& i:QVector<QString>(
        {
            "Dagon",
            "WoodlandSpirit", "Caranthir", "GeraltIgni", "GeEls",
            "CroneWeavess", "CroneWhispess", "CroneBrewess", "Frightener", "Roach", "BekkersTwistedMirror",
            "FirstLight", "BitingFrost", "ImpenetrableFog", "Foglet", "Foglet", "Foglet", "TorrentialRain", "Lacerate",
            "CelaenoHarpy", "Arachas", "Arachas", "Arachas", "EarthElemental", "EarthElemental", "EarthElemental",
            "Archgriffin", "VranWarrior", "VranWarrior", "CelaenoHarpy", "CelaenoHarpy"
        }
    ))
    {
        auto card = CardMeta::GetMetaByCardName(i);
        AllyCardGroup.InsertIntoCardGroup(*card);
        delete card;
    }
}


void GameController::InitializeNetwork()
{
    qDebug() << "Initializing network";
    // todo should be modified
    SetServerAddress("localhost");
    SetServerPort(6666);
    RegisterToHost();
    SendMessage("Hello server");
}
//</editor-fold>
