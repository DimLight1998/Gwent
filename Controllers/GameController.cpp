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
#include "../Models/Assets/Effects/TorrentialRain.hpp"
#include "../Models/Assets/Effects/ImpenetrableFog.hpp"
#include "../Models/Assets/Effects/BitingFrost.hpp"


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


void GameController::HandleRoundUpdate()
{
    // update weathers
    for (const auto& battleLineName :QVector<QString>({"EnemyMelee", "EnemyRanged", "EnemySiege"}))
    {
        auto battleLine = _battleField->GetBattleLineByName(battleLineName);
        switch (battleLine->GetWeather())
        {
        case BattleLine::WeatherEnum::Rain:
        {
            TorrentialRain::ExecuteDamage(this, battleLineName);
            break;
        }
        case BattleLine::WeatherEnum::Frost:
        {
            BitingFrost::ExecuteDamage(this, battleLineName);
            break;
        }
        case BattleLine::WeatherEnum::Fog:
        {
            ImpenetrableFog::ExecuteDamage(this, battleLineName);
            break;
        }
        case BattleLine::WeatherEnum::None:
        {
            break;
        }
        }
    }

    // update cards
    for (const auto& battleLineName :QVector<QString>({"AlliedMelee", "AlliedRanged", "AlliedSiege"}))
    {
        auto battleLine = _battleField->GetBattleLineByName(battleLineName);

        for (const auto item:battleLine->GetUnits())
        {
            dynamic_cast<Unit *>(_cardManager->GetCardById(item))->RoundUpdate();
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

        MoveCardFromCardsSetToCardsSet(card->GetCardId(), "AlliedGrave", 0);
        card->OnDeploy();
        card->OnDestroy();
    }

    Interacting->UpdateBattleFieldView();
}
//</editor-fold>


void GameController::StartGameEntry()
{
    InitializeNetwork();

    // todo remove hack
    HackBeforeStart();

    ResetGameData();

    for (int i = 0; i < 3; i++)
    {
        InitializeRoundGameData();
        bool isRoundOver = false;

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

        SynchronizeRemoteDataAllyHandOnly();

        while (!isRoundOver)
        {
            // check information
            QEventLoop eventLoop;
            QTimer::singleShot(500, &eventLoop, &QEventLoop::quit);
            eventLoop.exec();

            //<editor-fold desc="If is ally's turn">
            if (IsAllyTurn)
            {
                bool abdicate;
                int  cardId;

                // round update
                HandleRoundUpdate();
                Interacting->UpdateBattleFieldView();

                if (!IsAllyAbdicated)
                {
                    std::cout << "Ally input <================>\n";
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
            }
            //</editor-fold>

            if (IsAllyAbdicated && IsEnemyAbdicated)
            {
                isRoundOver = true;
                UpdateRoundPower();
                SendMessage("OperationDone|" + QString::number(PlayerNumber));
            }
        }

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
            std::cout << "Draw!";
            break;
        }
        else if (AllyTotalScore == 2)
        {
            std::cout << "You win!";
            break;
        }
        else if (EnemyTotalScore == 2)
        {
            std::cout << "You lose!";
            break;
        }
        //</editor-fold>
    }

    QMessageBox::information(nullptr, "End", "End");
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

    // the card group data should be ready already
    delete _battleField;
    delete _cardManager;
    delete Interacting;

    _battleField = new BattleField();
    _cardManager = new CardManager();
    Interacting  = new InteractingController(this);

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
        Interacting->UpdateBattleFieldView();
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

    _battleField->GetCardContainerByName("AlliedHand")->InsertCard(cardId, 0);
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
    SetRemoteServerAddress("localhost");
    SetRemoteServerPort(6666);
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


void GameController::SynchronizeRemoteDataAllyHandOnly()
{
    auto allyString  = "$HandCards:" + _battleField->GetCardContainerByName("AlliedHand")->ToString();
    auto cardsString = _cardManager->ToString();

    auto sendString      = "<Ally>" + allyString + "<Cards>" + cardsString;
    auto finalSendString = "SynchronizeStatus|" + QString::number(PlayerNumber) + "|" + sendString;

    SendMessage(finalSendString);
}


//<editor-fold desc="Hacking codes">
void GameController::HackBeforeStart()
{
    for (auto& i:QVector<QString>(
        {
            "Dagon",
            "WoodlandSpirit", "Caranthir", "GeraltIgni", "GeEls",
            "CroneWeavess", "CroneWhispess", "CroneBrewess", "Frightener", "Roach", "BekkersTwistedMirror",
            "FirstLight", "BitingFrost", "ImpenetrableFog", "Foglet", "Foglet", "Foglet", "TorrentialRain",
            "Lacerate",
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

//</editor-fold>
