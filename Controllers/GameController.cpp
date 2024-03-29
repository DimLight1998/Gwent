//
// Created on 2017/09/03 at 17:27.
//

#include <QtCore/QDateTime>
#include <c++/iostream>
#include <QtCore/QEventLoop>
#include <QtCore/QTimer>
#include <QtWidgets/QMessageBox>

#include "GameController.hpp"
#include "../Models/Containers/CardContainer.hpp"
#include "../Models/Card/Unit.hpp"
#include "../Models/Card/Effect.hpp"
#include "../Models/Meta/UnitMeta.hpp"
#include "../Models/Meta/EffectsMeta.hpp"
#include "../Models/Containers/BattleSide.hpp"
#include "../Utilities/RandomInteger.hpp"


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


GameController::GameController()
{
    Interacting  = new InteractingController(this);
    _battleField = new BattleField();
    _cardManager = new CardManager();
}


void GameController::SetInteracting(InteractingController *Interacting)
{
    GameController::Interacting = Interacting;
}


int GameController::GetNextId()
{
    static int  currentId             = 0;
    static bool isInitialValueUpdated = false;
    if (!isInitialValueUpdated)
    {
        if (PlayerNumber == 0)
        {
            currentId = 0;
        }
        else if (PlayerNumber == 1)
        {
            currentId = MaxCardPerSideInGame;
        }
        isInitialValueUpdated = true;
    }
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


bool GameController::AllyHasCards()
{
    return !_battleField->GetCardContainerByName("AlliedHand")->GetCards().empty();
}


//<editor-fold desc="Cards manipulation">

void GameController::DeployUnitToBattleLine(int cardId, const QString& battleLineName, int index)
{
    auto containerName = _battleField->getCardContainerContainingCard(cardId);
    MoveCardFromCardsSetToCardsSet(cardId, containerName, battleLineName, index);
    dynamic_cast<Unit *>(_cardManager->GetCardById(cardId))->SetSelectedLine(battleLineName);
    dynamic_cast<Unit *>(_cardManager->GetCardById(cardId))->SetSelectedIndex(index);
    _cardManager->GetCardById(cardId)->OnDeploy();
    Interacting->SetCheckPoint();
}


void GameController::SetWeatherToBattleLine(const QString& battleLineName, BattleLine::WeatherEnum weather)
{
    HandleWeatherChanged(battleLineName, _battleField->GetBattleLineByName(battleLineName)->GetWeather(), weather);
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
            Interacting->SetCheckPoint();

            return true;
        }
    }

    return false;
}


int GameController::SpawnCard(const QString& cardName, const QString& containerOrBattleLineName, int index)
{
    auto card = Card::SpawnCardByName(cardName, this);
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
        Interacting->SetCheckPoint();
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
        Interacting->SetCheckPoint();
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
            Interacting->SetCheckPoint();
        }
        else if (_battleField->IsABattleLine(destinationCardsSetName))
        {
            auto destinationBattleLine = _battleField->GetBattleLineByName(destinationCardsSetName);
            destinationBattleLine->InsertUnit(id, index);
            Interacting->SetCheckPoint();
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


void GameController::DeployTheCardOfId(int id)
{
    auto card = _cardManager->GetCardById(id);
    qDebug() << card->GetCardMetaInfo()->GetName();
    if (Unit::IsCardUnit(card))
    {
        QString deployLine;
        int     deployIndex;

        auto isValid = false;

        do
        {
            Interacting->GetSelectedUnitDeployLocation(deployLine, deployIndex);
            qDebug() << deployLine;
            QString prefix = (dynamic_cast<UnitMeta *>(card->GetCardMetaInfo())->IsLoyal()) ? "Allied" : "Enemy";

            qDebug() << deployLine;

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
            Interacting->SetCheckPoint();
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

        MoveCardFromCardsSetToCardsSet(card->GetCardId(), "AlliedGrave", 0);
        card->OnDeploy();
        card->OnDestroy();
    }

    Interacting->SetCheckPoint();
}
//</editor-fold>


void GameController::StartGameEntry()
{
    InitializeNetwork();

    ResetGameData();

    QString resultText = "";
    bool    hadRound3  = false;

    for (int i = 0; i < 3; i++)
    {
        if (i == 2)
        {
            hadRound3 = true;
        }

        InitializeRoundGameData();
        bool isRoundOver = false;

        SetSynchronizationPoint();

        //<editor-fold desc="Handle drawing cards and redraw">
        switch (i)
        {
        case 0:
        {
            for (int j = 0; j < 10; j++)
            {
                DrawOneCard();
            }
            HandleRedraw(3);
            break;
        }
        case 1:
        {
            DrawOneCard();
            DrawOneCard();
            HandleRedraw(1);
            break;
        }
        case 2:
        {
            DrawOneCard();
            HandleRedraw(1);
            break;
        }
        default:break;
        }
        //</editor-fold>

        SetSynchronizationPoint();

        SynchronizeRemoteDataAllySideOnly();

        SetSynchronizationPoint();

        while (!isRoundOver)
        {
            // check information
            QEventLoop eventLoop;
            QTimer::singleShot(500, &eventLoop, &QEventLoop::quit);
            eventLoop.exec();

            //<editor-fold desc="If is ally's turn">
            if (IsAllyTurn && !(IsAllyAbdicated && IsEnemyAbdicated))
            {
                bool abdicate;
                int  cardId;

                // round update
                HandleRoundUpdate();
                Interacting->UpdateBattleField();

                if (!IsAllyAbdicated)
                {
                    if (AllyHasCards())
                    {
                        Interacting->GetRoundInput(abdicate, cardId);
                    }
                    else
                    {
                        abdicate = true;
                    }
                }
                else
                {
                    abdicate = true;
                }

                if (abdicate)
                {
                    IsAllyAbdicated = true;
                    SendMessage("Abdicate|" + QString::number(PlayerNumber));
                }
                else
                {
                    DeployTheCardOfId(cardId);
                }

                SendMessage("OperationDone|" + QString::number(PlayerNumber));
                SynchronizeRemoteData();
                IsAllyTurn = false;
                Interacting->UpdateBattleField();
            }
            //</editor-fold>

            if (IsAllyAbdicated && IsEnemyAbdicated)
            {
                SetSynchronizationPoint();

                isRoundOver = true;
                UpdateRoundPower();

                auto totalPower = GetBattleLineScores();
                switch (i)
                {
                case 0:
                {
                    AllyRound1Score  = totalPower[3] + totalPower[4] + totalPower[5];
                    EnemyRound1Score = totalPower[0] + totalPower[1] + totalPower[2];
                    break;
                }
                case 1:
                {
                    AllyRound2Score  = totalPower[3] + totalPower[4] + totalPower[5];
                    EnemyRound2Score = totalPower[0] + totalPower[1] + totalPower[2];
                    break;
                }
                case 2:
                {
                    AllyRound3Score  = totalPower[3] + totalPower[4] + totalPower[5];
                    EnemyRound3Score = totalPower[0] + totalPower[1] + totalPower[2];
                    break;
                }
                }
            }
        }

        SetSynchronizationPoint();

        //<editor-fold desc="Statistics">
        if (AllyRoundPower > EnemyRoundPower)
        {
            AllyTotalScore++;
            IsAllyTurn = true;
        }
        else if (EnemyRoundPower > AllyRoundPower)
        {
            EnemyTotalScore++;
            IsAllyTurn = false;
        }
        else
        {
            AllyTotalScore++;
            EnemyTotalScore++;

            if (i + 2 < 4)
            {
                if (PlayerNumber == 0)
                {
                    IsAllyTurn = (FirstMoveInfo.split('|')[i + 2] == "0");
                }
                else if (PlayerNumber == 1)
                {
                    IsAllyTurn = (FirstMoveInfo.split('|')[i + 2] == "1");
                }
            }
        }

        if (AllyTotalScore == 2 && EnemyTotalScore == 2)
        {
            resultText = "Draw";
            break;
        }
        else if (AllyTotalScore == 2)
        {
            resultText = "You Win!";
            break;
        }
        else if (EnemyTotalScore == 2)
        {
            resultText = "You Lose!";
            break;
        }

        //</editor-fold>

        SetSynchronizationPoint();

        // clear all units and weathers
        QVector<int> units;
        for (const auto& item:QVector<QString>({"AlliedSiege", "AlliedRanged", "AlliedMelee"}))
        {
            auto battleLine = _battleField->GetBattleLineByName(item);
            battleLine->SetWeather(BattleLine::WeatherEnum::None);

            for (auto unit:battleLine->GetUnits())
            {
                units.append(unit);
            }
        }

        for (auto unit:units)
        {
            dynamic_cast<Unit *>(_cardManager->GetCardById(unit))->Destroy();
        }

        SetSynchronizationPoint();

        SynchronizeRemoteDataAllySideOnly();

        SetSynchronizationPoint();
    }

    if (hadRound3)
    {
        Interacting->InformResult(
            resultText,
            AllyRound1Score,
            AllyRound2Score,
            AllyRound3Score,
            EnemyRound1Score,
            EnemyRound2Score,
            EnemyRound3Score
        );
    }
    else
    {
        Interacting->InformResult(
            resultText,
            AllyRound1Score,
            AllyRound2Score,
            EnemyRound1Score,
            EnemyRound2Score
        );
    }

    Unregister();
}


void GameController::ResetGameData()
{
    std::cout << "Getting playing order...\n";

    IsAllyAbdicated  = false;
    IsEnemyAbdicated = false;
    PlayerNumber     = -1;

    AllyTotalScore  = 0;
    EnemyTotalScore = 0;

    IsAllyTurn = false;

    auto localAddress = GetLocalAddress();
    auto localPort    = ClientServer->serverPort();
    SendMessage("PLAYER|" + localAddress + "|" + QString::number(localPort));

    // before indexing, we need to know whether we are the first to start
    // we need a lock to lock this
    // wait until both sides are ready
    QEventLoop eventLoop;
    connect(this, &GameController::BothSidesGetReady, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();
    // now we kow who is player 0 and who is player 1, and we can allocate id for them

    // index the cards
    for (const auto& i:AllyCardGroup.GetCardMetaGroup())
    {
        auto card = Card::SpawnCardByName(i.GetName(), this);
        card->SetCardId(GetNextId());
        auto id = card->GetCardId();
        _cardManager->RegisterCard(card);

        _battleField->GetCardContainerByName("AlliedDeck")->InsertCard(id, 0);
    }

    InitializeAllyCardData();

    SynchronizeRemoteDataAllySideOnly();

    // setting up special handlers
    for (const auto& item :QVector<QString>(
        {
            "FirstLight", "BitingFrost", "ImpenetrableFog", "Foglet", "TorrentialRain",
            "Lacerate", "CommandersHorn", "BekkersTwistedMirror", "GeraltIgni", "Dagon",
            "GeEls", "CelaenoHarpy", "WoodlandSpirit", "EarthElemental", "CroneWeavess",
            "CroneWhispess", "CroneBrewess", "Archgriffin", "Caranthir", "Frightener",
            "UnseenElder", "Arachas", "ArachasBehemoth", "VranWarrior", "ThunderboltPotion",
            "Roach", "WildHuntRider", "HarpyEgg", "HarpyHatchling", "RabidWolf",
            "LesserEarthElemental", "ArachasHatchling", "ClearSkies", "Rally"
        }))
    {
        SpecialHandlers.append(Card::SpawnCardByName(item, this));
    }
}


void GameController::InitializeRoundGameData()
{
    IsAllyAbdicated  = false;
    IsEnemyAbdicated = false;

    AllyRoundPower  = 0;
    EnemyRoundPower = 0;
}


void GameController::HandleMessage(const QString& message)
{
    if (message.startsWith("ALLOCATE"))
    {
        auto slices      = message.split('|', QString::SkipEmptyParts);
        auto ip          = slices[1];
        auto port        = slices[2].toInt();
        auto playerOrder = slices[3].toInt();

        if (ip == GetLocalAddress() && port == ClientServer->serverPort())
        {
            PlayerNumber = playerOrder;
        }

        return;
    }

    if (message.startsWith("OperationDone"))
    {
        auto playerNumber = message.split('|', QString::SkipEmptyParts)[1].toInt();
        if (playerNumber != PlayerNumber)
        {
            IsAllyTurn = true;
        }
        return;
    }

    if (message.startsWith("SynchronizeStatus"))
    {
        SynchronizeLocalData(message);
        return;
    }

    if (message.startsWith("Abdicate"))
    {
        auto playerNumber = message.split('|')[1].toInt();
        if (playerNumber != PlayerNumber)
        {
            IsEnemyAbdicated = true;
        }
        return;
    }

    if (message.startsWith("FIRST"))
    {
        if (PlayerNumber == 0)
        {
            IsAllyTurn = (message.split('|')[1] == "0");
        }
        else if (PlayerNumber == 1)
        {
            IsAllyTurn = (message.split('|')[1] == "1");
        }

        FirstMoveInfo = message;

        emit(BothSidesGetReady());

        return;
    }

    if (message.startsWith("UNLOCK"))
    {
        IsLocked = false;
    }
}


void GameController::SynchronizeLocalData(const QString& message)
{
    auto senderNumber  = message.split('|', QString::SkipEmptyParts)[1].toInt();
    auto statusMessage = message.split('|', QString::SkipEmptyParts)[2];

    if (senderNumber != PlayerNumber)
    {
        qDebug() << "****sync based on****" << message;
        qDebug() << "Dealing!===============";
        // todo last work stops here at 13:08 on 2017/09/10

        auto statusMessageSlices = statusMessage.split("<", QString::SkipEmptyParts);
        for (const auto& item:statusMessageSlices)
        {
            if (item.startsWith("Ally") || item.startsWith("Enemy"))
            {
                QString prefix;
                if (item.startsWith("Ally"))
                {
                    prefix = "Enemy";
                }
                else if (item.startsWith("Enemy"))
                {
                    prefix = "Allied";
                }

                auto itemSlices = item.split('$', QString::SkipEmptyParts);

                for (int i = 1; i < itemSlices.size(); i++)
                {

                    auto cardsSetName    = itemSlices[i].split(':', QString::KeepEmptyParts)[0];
                    auto weatherAndCards = itemSlices[i].split(':', QString::KeepEmptyParts)[1];

                    if (cardsSetName.endsWith("Line"))
                    {
                        _battleField
                            ->GetBattleLineByName(prefix + cardsSetName.left(cardsSetName.length() - 4))
                            ->UpdateFromString(weatherAndCards);
                        continue;
                    }

                    if (cardsSetName.endsWith("Cards"))
                    {
                        _battleField
                            ->GetCardContainerByName(prefix + cardsSetName.left(cardsSetName.length() - 5))
                            ->UpdateFromString(weatherAndCards);

                        continue;
                    }
                }

                continue;
            }

            if (item.startsWith("Cards"))
            {
                _cardManager->UpdateFromString(item.split('>', QString::SkipEmptyParts)[1], this);
            }
        }
        qDebug() << "Synchronized";
        Interacting->UpdateBattleField();
    }
}


void GameController::InitializeAllyCardData()
{
    std::cout << "Initializing card data\n";
    // shuffle the deck
    auto deck = _battleField->GetCardContainerByName("AlliedDeck")->GetCards();
    _battleField->GetCardContainerByName("AlliedDeck")->ClearCardContainer();

    std::mt19937 g(static_cast<unsigned int>(RandomInteger::GetRandomInteger()));

    std::shuffle(deck.begin(), deck.end(), g);

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

    // rebuild the deck
    for (auto i:deck)
    {
        _battleField->GetCardContainerByName("AlliedDeck")->InsertCard(i, 0);
    }
}


void GameController::DrawOneCard()
{
    auto cardId = _battleField->GetCardContainerByName("AlliedDeck")->GetCards()[0];
    _battleField->GetCardContainerByName("AlliedDeck")->RemoveCardOfId(cardId);

    _battleField->GetCardContainerByName("AlliedHand")->InsertCard(cardId, 0);
}


void GameController::RedrawOneCard(int originalCardId)
{
    AllyCardBlackList.append(_cardManager->GetCardById(originalCardId)->GetCardMetaInfo()->GetName());

    bool valid    = false;
    bool hasValid = false;

    for (auto item:_battleField->GetCardContainerByName("AlliedDeck")->GetCards())
    {
        if (!AllyCardBlackList.contains(_cardManager->GetCardById(item)->GetCardMetaInfo()->GetName()))
        {
            hasValid = true;
        }
    }

    int cardId = -1;

    if (hasValid)
    {
        while (!valid)
        {
            cardId = _battleField->GetCardContainerByName("AlliedDeck")->GetCards()[0];
            _battleField->GetCardContainerByName("AlliedDeck")->RemoveCardOfId(cardId);

            if (!AllyCardBlackList.contains(_cardManager->GetCardById(cardId)->GetCardMetaInfo()->GetName()))
            {
                valid = true;
            }
            else
            {
                auto size = _battleField->GetCardContainerByName("AlliedDeck")->GetCards().size();
                _battleField->GetCardContainerByName("AlliedDeck")->InsertCard(cardId, size);
            }
        }
    }
    else
    {
        cardId = _battleField->GetCardContainerByName("AlliedDeck")->GetCards()[0];
        _battleField->GetCardContainerByName("AlliedDeck")->RemoveCardOfId(cardId);
    }

    auto handSize       = _battleField->GetCardContainerByName("AlliedHand")->GetCards().size();
    int  insertionIndex = 0;

    for (int i = 0; i < handSize; i++)
    {
        if (_battleField->GetCardContainerByName("AlliedHand")->GetCards()[i] == originalCardId)
        {
            insertionIndex = i;
            break;
        }
    }

    _battleField->GetCardContainerByName("AlliedHand")->InsertCard(cardId, insertionIndex);

    auto deckSize = _battleField->GetCardContainerByName("AlliedDeck")->GetCards().size();
    MoveCardFromCardsSetToCardsSet(originalCardId, "AlliedHand", "AlliedDeck", deckSize);
}


void GameController::HandleRedraw(int redrawLimit)
{
    for (int j = 0; j < redrawLimit; j++)
    {
        auto hand = _battleField->GetCardContainerByName("AlliedHand")->GetCards();

        for (int k = hand.size() - 1; k >= 0; k--)
        {
            if (_cardManager->GetCardById(hand[k])->GetCardMetaInfo()->GetCardType()
                == CardMeta::CardTypeEnum::Leader)
            {
                hand.remove(k);
                break;
            }
        }

        auto originalCardId = Interacting->GetSelectedCardFromExistingCardsAbdicable(hand);
        if (originalCardId == -1)
        {
            break;
        }
        else
        {
            RedrawOneCard(originalCardId);
        }
    }
}


void GameController::InitializeNetwork()
{
    qDebug() << "Initializing network";
    // todo should be modified
    SetRemoteServerAddress(AddressOfRemoteServer);
    SetRemoteServerPort(PortOfRemoteServer);
    RegisterToHost();
}


void GameController::SynchronizeRemoteData()
{
    auto allyString  = _battleField->GetAlliedBattleSide()->ToString();
    auto enemyString = _battleField->GetEnemyBattleSide()->ToString();
    auto cardsString = _cardManager->ToString();

    auto sendString      = "<Ally>" + allyString + "<Enemy>" + enemyString + "<Cards>" + cardsString;
    auto finalSendString = "SynchronizeStatus|" + QString::number(PlayerNumber) + "|" + sendString;

    qDebug() << "****Sending info to sync remote****" << finalSendString;

    SendMessage(finalSendString);
}


void GameController::SynchronizeRemoteDataAllySideOnly()
{
    auto allyString  = _battleField->GetAlliedBattleSide()->ToString();
    auto cardsString = _cardManager->ToString();

    auto sendString      = "<Ally>" + allyString + "<Cards>" + cardsString;
    auto finalSendString = "SynchronizeStatus|" + QString::number(PlayerNumber) + "|" + sendString;

    qDebug() << "****Sending info to sync remote (Ally ONLY)****" << finalSendString;

    SendMessage(finalSendString);
}


QVector<int> GameController::GetBattleLineScores()
{
    auto alliedMeleePower  = 0;
    auto alliedRangedPower = 0;
    auto alliedSiegePower  = 0;
    auto enemyMeleePower   = 0;
    auto enemyRangedPower  = 0;
    auto enemySiegePower   = 0;

    for (const auto item:_battleField->GetBattleLineByName("AlliedMelee")->GetUnits())
    {
        auto unit = _cardManager->GetCardById(item);
        alliedMeleePower += dynamic_cast<Unit *>(unit)->GetPower();
    }

    for (const auto item:_battleField->GetBattleLineByName("AlliedRanged")->GetUnits())
    {
        auto unit = _cardManager->GetCardById(item);
        alliedRangedPower += dynamic_cast<Unit *>(unit)->GetPower();
    }

    for (const auto item:_battleField->GetBattleLineByName("AlliedSiege")->GetUnits())
    {
        auto unit = _cardManager->GetCardById(item);
        alliedSiegePower += dynamic_cast<Unit *>(unit)->GetPower();
    }

    for (const auto item:_battleField->GetBattleLineByName("EnemyMelee")->GetUnits())
    {
        auto unit = _cardManager->GetCardById(item);
        enemyMeleePower += dynamic_cast<Unit *>(unit)->GetPower();
    }

    for (const auto item:_battleField->GetBattleLineByName("EnemyRanged")->GetUnits())
    {
        auto unit = _cardManager->GetCardById(item);
        enemyRangedPower += dynamic_cast<Unit *>(unit)->GetPower();
    }

    for (const auto item:_battleField->GetBattleLineByName("EnemySiege")->GetUnits())
    {
        auto unit = _cardManager->GetCardById(item);
        enemySiegePower += dynamic_cast<Unit *>(unit)->GetPower();
    }

    return QVector<int>(
        {
            enemySiegePower,
            enemyRangedPower,
            enemyMeleePower,
            alliedMeleePower,
            alliedRangedPower,
            alliedSiegePower
        });
}


QVector<QString> GameController::GetBattleLineWeathers()
{
    return QVector<QString>(
        {
            _battleField->GetBattleLineByName("EnemySiege")->GetWeatherString(),
            _battleField->GetBattleLineByName("EnemyRanged")->GetWeatherString(),
            _battleField->GetBattleLineByName("EnemyMelee")->GetWeatherString(),
            _battleField->GetBattleLineByName("AlliedMelee")->GetWeatherString(),
            _battleField->GetBattleLineByName("AlliedRanged")->GetWeatherString(),
            _battleField->GetBattleLineByName("AlliedSiege")->GetWeatherString()
        }
    );
}


bool GameController::GetIsAllyTurn()
{
    return IsAllyTurn;
}


void GameController::UpdateRoundPower()
{
    AllyRoundPower  = 0;
    EnemyRoundPower = 0;

    for (const auto& battleLineName :QVector<QString>({"AlliedMelee", "AlliedRanged", "AlliedSiege"}))
    {
        auto            battleLine = _battleField->GetBattleLineByName(battleLineName);
        for (const auto item:battleLine->GetUnits())
        {
            auto unit = _cardManager->GetCardById(item);
            AllyRoundPower += dynamic_cast<Unit *>(unit)->GetPower();
        }
    }

    for (const auto& battleLineName :QVector<QString>({"EnemyMelee", "EnemyRanged", "EnemySiege"}))
    {
        auto            battleLine = _battleField->GetBattleLineByName(battleLineName);
        for (const auto item:battleLine->GetUnits())
        {
            auto unit = _cardManager->GetCardById(item);
            EnemyRoundPower += dynamic_cast<Unit *>(unit)->GetPower();
        }
    }
}


void GameController::SetAddressOfRemoteServer(const QString& AddressOfRemoteServer)
{
    GameController::AddressOfRemoteServer = AddressOfRemoteServer;
}


void GameController::SetPortOfRemoteServer(quint16 PortOfRemoteServer)
{
    GameController::PortOfRemoteServer = PortOfRemoteServer;
}


void GameController::SetAllyCardGroup(const CardGroup& AllyCardGroup)
{
    GameController::AllyCardGroup = AllyCardGroup;
}


void GameController::SetSynchronizationPoint()
{

    IsLocked = true;
    SendMessage("READYUNLOCK");

    while (IsLocked)
    {
        QEventLoop eventLoop;
        QTimer::singleShot(500, &eventLoop, &QEventLoop::quit);
        eventLoop.exec();
    }
}


void GameController::HandleRoundUpdate()
{
    SynchronizeRemoteData();
    for (const auto item:SpecialHandlers)
    {
        item->OnRoundUpdateHandler();
    }

    // update cards
    for (const auto& battleLineName :QVector<QString>({"AlliedMelee", "AlliedRanged", "AlliedSiege"}))
    {
        auto battleLine = _battleField->GetBattleLineByName(battleLineName);

        for (const auto item:battleLine->GetUnits())
        {
            dynamic_cast<Unit *>(_cardManager->GetCardById(item))->RoundUpdate();
            Interacting->SetCheckPoint();
        }
    }

    SynchronizeRemoteData();
}


void GameController::HandleCardDeployed(int cardId)
{
    SynchronizeRemoteData();
    for (const auto item:SpecialHandlers)
    {
        item->OnOtherCardDeployHandler(cardId);
    }
    SynchronizeRemoteData();
}


void GameController::HandleWeatherChanged(
    const QString& battleLineName, BattleLine::WeatherEnum originalWeather, BattleLine::WeatherEnum newWeather
)
{
    SynchronizeRemoteData();
    for (const auto item:SpecialHandlers)
    {
        item->OnWeatherChangedHandler(battleLineName, originalWeather, newWeather);
    }
    SynchronizeRemoteData();
}


void GameController::HandleUnitSwallowed(int swallowedUnitId)
{
    SynchronizeRemoteData();
    dynamic_cast<Unit *>(GetCardManager()->GetCardById(swallowedUnitId))->Destroy();

    for (const auto item:SpecialHandlers)
    {
        item->OnOtherUnitSwallowedHandler(swallowedUnitId);
    }
    SynchronizeRemoteData();
}

//</editor-fold>
