//
// Created on 2017/09/05 at 09:58.
//

#include <QtWidgets/QInputDialog>
#include <QtCore/QTimer>
#include "InteractingController.hpp"
#include "../Views/States/CardSelectionState.hpp"
#include "../Models/Containers/CardContainer.hpp"
#include "../Views/States/GamePlayingState.hpp"
#include "../Views/Widgets/CardButton.hpp"
#include "../Views/States/ResultState.hpp"


GameController *InteractingController::GetController() const
{
    return Controller;
}


InteractingController::InteractingController(GameController *Controller)
    : Controller(Controller)
{ }


void InteractingController::SetController(GameController *Controller)
{
    InteractingController::Controller = Controller;
}


int InteractingController::GetSelectedCardFromExistingCards(const QVector<int>& existingCardsId)
{
    auto cardSelectionState =
             PlayingState->GetBase()->GetSharedData("CardSelectionState").value<CardSelectionState *>();
    cardSelectionState->ClearAllCards();

    QVector<CardButton *> deleteList;

    for (const auto item:existingCardsId)
    {
        auto *cardButton = new CardButton(nullptr, item, PlayingState->GetMainGameController()->GetCardManager());
        deleteList.append(cardButton);
        cardSelectionState->InsertCard(cardButton);
    }

    PlayingState->GetBase()->SwitchToState("CardSelection");

    cardSelectionState->RefreshMapper();

    cardSelectionState->SetAbdicable(false);

    QEventLoop eventLoop;

    int selected;

    auto connection = QObject::connect
        (
            cardSelectionState->SignalMapper,
            static_cast<void (QSignalMapper::*)(int)>(&QSignalMapper::mapped),
            [&eventLoop, &selected](int cardId)
            {
              selected = cardId;
              eventLoop.quit();
            }
        );

    eventLoop.exec();

    for (const auto item:deleteList)
    {
        delete item;
    }

    QObject::disconnect(connection);

    PlayingState->GetBase()->SwitchToState("GamePlaying");

    return selected;
}


int InteractingController::GetSelectedCardFromExistingCardsAbdicable(const QVector<int>& existingCardsId)
{
    auto cardSelectionState =
             PlayingState->GetBase()->GetSharedData("CardSelectionState").value<CardSelectionState *>();
    cardSelectionState->ClearAllCards();

    QVector<CardButton *> deleteList;

    for (const auto item:existingCardsId)
    {
        auto *cardButton = new CardButton(nullptr, item, PlayingState->GetMainGameController()->GetCardManager());
        deleteList.append(cardButton);
        cardSelectionState->InsertCard(cardButton);
    }

    PlayingState->GetBase()->SwitchToState("CardSelection");

    cardSelectionState->RefreshMapper();

    cardSelectionState->SetAbdicable(true);

    QEventLoop eventLoop;

    int selected;

    auto signalMapConncetion = QObject::connect
        (
            cardSelectionState->SignalMapper,
            static_cast<void (QSignalMapper::*)(int)>(&QSignalMapper::mapped),// todo can't arrive here
            [&eventLoop, &selected](int cardId)
            {
              selected = cardId;
              eventLoop.quit();
            }
        );

    auto doneButtonConnection = QObject::connect
        (
            cardSelectionState,
            &CardSelectionState::ClickOnDoneButton,
            [&eventLoop, &selected]
            {
              selected = -1;
              eventLoop.quit();
            }
        );

    eventLoop.exec();

    for (const auto item:deleteList)
    {
        delete item;
    }

    QObject::disconnect(signalMapConncetion);
    QObject::disconnect(doneButtonConnection);

    PlayingState->GetBase()->SwitchToState("GamePlaying");
    return selected;
}


void InteractingController::GetRoundInput(bool& abdicate, int& selectedCardId)
{
    PlayingState->RefreshCardsConnections();

    bool isAbdicate = false;
    int  id;

    QEventLoop eventLoop;

    auto signalMapConnection = QObject::connect(
        PlayingState->SignalMapper,
        static_cast<void (QSignalMapper::*)(int)>(&QSignalMapper::mapped),
        [&id, &eventLoop](int cardId)
        {
          id = cardId;
          eventLoop.quit();
        }
    );

    auto abdicateButtonConnection = QObject::connect(
        PlayingState,
        &GamePlayingState::ClickedOnAbdicateButton,
        [&isAbdicate, &eventLoop]
        {
          isAbdicate = true;
          eventLoop.quit();
        }
    );

    eventLoop.exec();

    QObject::disconnect(signalMapConnection);
    QObject::disconnect(abdicateButtonConnection);

    abdicate       = isAbdicate;
    selectedCardId = id;
}


CardMeta InteractingController::GetSelectedCardFromSpanningCards(const QVector<CardMeta *>& spawningCardsMeta)
{
    auto cardSelectionState =
             PlayingState->GetBase()->GetSharedData("CardSelectionState").value<CardSelectionState *>();
    cardSelectionState->ClearAllCards();

    QVector<CardButton *> deleteList;

    auto temporaryCardManager = new CardManager();

    for (int i = 0; i < spawningCardsMeta.size(); i++)
    {
        auto card = Card::SpawnCardByName(spawningCardsMeta[i]->GetName(), nullptr);
        card->SetCardId(i);
        temporaryCardManager->RegisterCard(card);
    }

    for (int i = 0; i < spawningCardsMeta.size(); i++)
    {
        auto *cardButton = new CardButton(nullptr, i, temporaryCardManager);
        deleteList.append(cardButton);
        cardSelectionState->InsertCard(cardButton);
    }

    PlayingState->GetBase()->SwitchToState("CardSelection");

    cardSelectionState->RefreshMapper();

    cardSelectionState->SetAbdicable(false);

    QEventLoop eventLoop;

    int selected;

    auto connection = QObject::connect
        (
            cardSelectionState->SignalMapper,
            static_cast<void (QSignalMapper::*)(int)>(&QSignalMapper::mapped),
            [&eventLoop, &selected](int cardId)
            {
              selected = cardId;
              eventLoop.quit();
            }
        );

    eventLoop.exec();

    for (const auto item:deleteList)
    {
        delete item;
    }
    QObject::disconnect(connection);

    delete temporaryCardManager;
    qDebug() << spawningCardsMeta[selected]->GetName();

    PlayingState->GetBase()->SwitchToState("GamePlaying");

    return *(spawningCardsMeta[selected]);
}


int InteractingController::GetSelectedCardFromBattleField()
{
    PlayingState->RefreshCardsConnections();

    QEventLoop eventLoop;

    int id;

    auto connection = QObject::connect(
        PlayingState->SignalMapper,
        static_cast<void (QSignalMapper::*)(int)>(&QSignalMapper::mapped),
        [&id, &eventLoop](int cardId)
        {
          id = cardId;
          eventLoop.quit();
        }
    );

    eventLoop.exec();

    QObject::disconnect(connection);

    return id;
}


void InteractingController::GetSelectedUnitDeployLocation(QString& deployBattleLine, int& deployIndex)
{
    QEventLoop eventLoop;

    auto enemySiegeConnection   = QObject::connect(
        PlayingState, &GamePlayingState::ClickedOnEnemySiege,
        [&deployBattleLine, &eventLoop, &deployIndex](int index)
        {
          deployBattleLine = "EnemySiege";
          deployIndex      = index;
          eventLoop.quit();
        });
    auto enemyRangedConnection  = QObject::connect(
        PlayingState, &GamePlayingState::ClickedOnEnemyRanged,
        [&deployBattleLine, &eventLoop, &deployIndex](int index)
        {
          deployBattleLine = "EnemyRanged";
          deployIndex      = index;
          eventLoop.quit();
        });
    auto enemyMeleeConnection   = QObject::connect(
        PlayingState, &GamePlayingState::ClickedOnEnemyMelee,
        [&deployBattleLine, &eventLoop, &deployIndex](int index)
        {
          deployBattleLine = "EnemyMelee";
          deployIndex      = index;
          eventLoop.quit();
        });
    auto alliedMeleeConnection  = QObject::connect(
        PlayingState, &GamePlayingState::ClickedOnAlliedMelee,
        [&deployBattleLine, &eventLoop, &deployIndex](int index)
        {
          deployBattleLine = "AlliedMelee";
          deployIndex      = index;
          eventLoop.quit();
        });
    auto alliedRangedConnection = QObject::connect(
        PlayingState, &GamePlayingState::ClickedOnAlliedRanged,
        [&deployBattleLine, &eventLoop, &deployIndex](int index)
        {
          deployBattleLine = "AlliedRanged";
          deployIndex      = index;
          eventLoop.quit();
        });
    auto alliedSiegeConnection  = QObject::connect(
        PlayingState, &GamePlayingState::ClickedOnAlliedSiege,
        [&deployBattleLine, &eventLoop, &deployIndex](int index)
        {
          deployBattleLine = "AlliedSiege";
          deployIndex      = index;
          eventLoop.quit();
        });

    eventLoop.exec();

    QObject::disconnect(enemySiegeConnection);
    QObject::disconnect(enemyRangedConnection);
    QObject::disconnect(enemyMeleeConnection);
    QObject::disconnect(alliedMeleeConnection);
    QObject::disconnect(alliedRangedConnection);
    QObject::disconnect(alliedSiegeConnection);
}


QString InteractingController::GetSelectedEffectDeployBattleLine()
{
    int choose;

    QEventLoop eventLoop;

    auto enemySiegeConnection   = QObject::connect
        (PlayingState, &GamePlayingState::ClickedOnEnemySiege, [&choose, &eventLoop]
        {
          choose = 1;
          eventLoop.quit();
        });
    auto enemyRangedConnection  = QObject::connect
        (PlayingState, &GamePlayingState::ClickedOnEnemyRanged, [&choose, &eventLoop]
        {
          choose = 2;
          eventLoop.quit();
        });
    auto enemyMeleeConnection   = QObject::connect
        (PlayingState, &GamePlayingState::ClickedOnEnemyMelee, [&choose, &eventLoop]
        {
          choose = 3;
          eventLoop.quit();
        });
    auto alliedMeleeConnection  = QObject::connect
        (PlayingState, &GamePlayingState::ClickedOnAlliedMelee, [&choose, &eventLoop]
        {
          choose = 4;
          eventLoop.quit();
        });
    auto alliedRangedConnection = QObject::connect
        (PlayingState, &GamePlayingState::ClickedOnAlliedRanged, [&choose, &eventLoop]
        {
          choose = 5;
          eventLoop.quit();
        });
    auto alliedSiegeConnection  = QObject::connect
        (PlayingState, &GamePlayingState::ClickedOnAlliedSiege, [&choose, &eventLoop]
        {
          choose = 6;
          eventLoop.quit();
        });

    eventLoop.exec();

    QObject::disconnect(enemySiegeConnection);
    QObject::disconnect(enemyRangedConnection);
    QObject::disconnect(enemyMeleeConnection);
    QObject::disconnect(alliedMeleeConnection);
    QObject::disconnect(alliedRangedConnection);
    QObject::disconnect(alliedSiegeConnection);

    switch (choose)
    {
    case 1:return "EnemySiege";
    case 2:return "EnemyRanged";
    case 3:return "EnemyMelee";
    case 4:return "AlliedMelee";
    case 5:return "AlliedRanged";
    case 6:return "AlliedSiege";
    }
}


void InteractingController::GetGlobalSelection()
{
    QEventLoop eventLoop;

    QObject::connect(PlayingState, &GamePlayingState::ClickedOnEnemySiege, &eventLoop, &QEventLoop::quit);
    QObject::connect(PlayingState, &GamePlayingState::ClickedOnEnemyRanged, &eventLoop, &QEventLoop::quit);
    QObject::connect(PlayingState, &GamePlayingState::ClickedOnEnemyMelee, &eventLoop, &QEventLoop::quit);
    QObject::connect(PlayingState, &GamePlayingState::ClickedOnAlliedMelee, &eventLoop, &QEventLoop::quit);
    QObject::connect(PlayingState, &GamePlayingState::ClickedOnAlliedRanged, &eventLoop, &QEventLoop::quit);
    QObject::connect(PlayingState, &GamePlayingState::ClickedOnAlliedSiege, &eventLoop, &QEventLoop::quit);

    eventLoop.exec();
}


void InteractingController::UpdateBattleField()
{
    PlayingState->ClearBattleLine();
    PlayingState->ClearHand();

    for (const auto& item:QVector<QString>({"EnemySiege", "EnemyRanged", "EnemyMelee", "AlliedMelee", "AlliedRanged",
                                            "AlliedSiege"}))
    {
        auto units = Controller->GetBattleField()->GetBattleLineByName(item)->GetUnits();

        for (int i = 0; i < units.size(); i++)
        {
            PlayingState->InsertCardToBattleLine(item, units[i], i);
        }
    }

    for (const auto& item:QVector<QString>({"EnemyHand", "AlliedHand"}))
    {
        auto cards = Controller->GetBattleField()->GetCardContainerByName(item)->GetCards();

        QString faction;
        if (item == "EnemyHand")
        {
            faction = "Enemy";
        }
        else if (item == "AlliedHand")
        {
            faction = "Ally";
        }

        for (int i = 0; i < cards.size(); i++)
        {
            PlayingState->InsertCardToHand(faction, cards[i], i);
        }
    }

    PlayingState->RefreshCardsConnections();

    PlayingState->UpdateUi(
        Controller->GetBattleLineScores(),
        Controller->GetBattleLineWeathers(),
        Controller->GetIsAllyTurn()
    );
}


void InteractingController::SetPlayingState(GamePlayingState *PlayingState)
{
    InteractingController::PlayingState = PlayingState;
}


void InteractingController::SetCheckPoint()
{
    Controller->SynchronizeRemoteDataAllySideOnly();

    QEventLoop eventLoop;

    QTimer::singleShot(150, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    UpdateBattleField();

    QTimer::singleShot(150, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();
}


void InteractingController::InformResult(
    bool isWinner,
    int allyRound1,
    int allyRound2,
    int allyRound3,
    int enemyRound1,
    int enemyRound2,
    int enemyRound3
)
{
    PlayingState->GetBase()->SwitchToState("Result");
    auto resultState = PlayingState->GetBase()->GetSharedData("ResultState").value<ResultState *>();
    resultState->SetResult(
        isWinner, allyRound1,
        allyRound2,
        allyRound3,
        enemyRound1,
        enemyRound2,
        enemyRound3
    );
}


void InteractingController::InformResult(
    bool isWinner,
    int allyRound1,
    int allyRound2,
    int enemyRound1,
    int enemyRound2
)
{
    PlayingState->GetBase()->SwitchToState("Result");
    auto resultState = PlayingState->GetBase()->GetSharedData("ResultState").value<ResultState *>();
    resultState->SetResult(
        isWinner,
        allyRound1,
        allyRound2,
        enemyRound1,
        enemyRound2
    );
}
