//
// Created on 2017/09/05 at 09:58.
//

#include <QtWidgets/QInputDialog>
#include "InteractingController.hpp"
#include "../Views/States/CardSelectionState.hpp"
#include "../Models/Containers/CardContainer.hpp"
#include "../Views/States/GamePlayingState.hpp"
#include "../Views/Widgets/CardButton.hpp"


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
        PlayingState->GetBase()->SwitchToState("CardSelection");
    }

    cardSelectionState->RefreshMapper();

    cardSelectionState->SetAbdicable(false);

    QEventLoop eventLoop;

    int selected;

    QObject::connect
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
        PlayingState->GetBase()->SwitchToState("CardSelection");
    }

    cardSelectionState->RefreshMapper();

    cardSelectionState->SetAbdicable(true);

    QEventLoop eventLoop;

    int selected;

    QObject::connect
        (
            cardSelectionState->SignalMapper,
            static_cast<void (QSignalMapper::*)(int)>(&QSignalMapper::mapped),// todo can't arrive here
            [&eventLoop, &selected](int cardId)
            {
              selected = cardId;
              eventLoop.quit();
            }
        );

    QObject::connect
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

    PlayingState->GetBase()->SwitchToState("GamePlaying");
    return selected;
}


void InteractingController::GetRoundInput(bool& abdicate, int& selectedCardId)
{
    PlayingState->RefreshCardsConnections();

    bool isAbdicate;
    int  id;

    QEventLoop eventLoop;

    QObject::connect(
        PlayingState->SignalMapper,
        static_cast<void (QSignalMapper::*)(int)>(&QSignalMapper::mapped),
        [&id, &eventLoop](int cardId)
        {
          id = cardId;
          eventLoop.quit();
        }
    );

    QObject::connect(
        PlayingState,
        &GamePlayingState::ClickedOnAbdicateButton,
        [&isAbdicate, &eventLoop]
        {
          isAbdicate = true;
          eventLoop.quit();
        }
    );

    eventLoop.exec();

    abdicate       = isAbdicate;
    selectedCardId = id;
}


CardMeta InteractingController::GetSelectedCardFromSpanningCards(const QVector<CardMeta *>& spawningCardsMeta)
{
    auto cardSelectionState =
             PlayingState->GetBase()->GetSharedData("CardSelectionState").value<CardSelectionState *>();
    cardSelectionState->ClearAllCards();

    QVector<CardButton *> deleteList;

    for (int i = 0; i < spawningCardsMeta.size(); i++)
    {
        auto *cardButton = new CardButton(nullptr, i, PlayingState->GetMainGameController()->GetCardManager());
        deleteList.append(cardButton);
        cardSelectionState->InsertCard(cardButton);
        PlayingState->GetBase()->SwitchToState("CardSelection");
    }

    cardSelectionState->RefreshMapper();

    cardSelectionState->SetAbdicable(false);

    QEventLoop eventLoop;

    int selected;

    QObject::connect
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

    PlayingState->GetBase()->SwitchToState("GamePlaying");

    return *(spawningCardsMeta[selected]);
}


int InteractingController::GetSelectedCardFromBattleField()
{
    PlayingState->RefreshCardsConnections();

    QEventLoop eventLoop;

    int id;

    QObject::connect(
        PlayingState->SignalMapper,
        static_cast<void (QSignalMapper::*)(int)>(&QSignalMapper::mapped),
        [&id, &eventLoop](int cardId)
        {
          id = cardId;
          eventLoop.quit();
        }
    );

    eventLoop.exec();

    return id;
}


void InteractingController::GetSelectedUnitDeployLocation(QString& deployBattleLine, int& deployIndex)
{
    //    std::cout << "You are now deploying the card to the battlefield, please input two integers" << std::endl;
    //    std::cout << "the first int represent the battle line, as following:" << std::endl;
    //    std::cout << "1 - AlliedMelee\n2 - AlliedRanged\n3 - AlliedSiege\n";
    //    std::cout << "4 - EnemyMelee\n5 - EnemyRanged\n6 - EnemySiege\n";
    //    std::cout << "the second int represent the index of the insertion\n";
    //
    //    int first  = QInputDialog::getInt(nullptr, "", "");
    //    int second = QInputDialog::getInt(nullptr, "", "");
    //
    //    //    int first;
    //    //    int second;
    //    //    std::cin >> first;
    //    //    std::cin >> second;
    //
    //    switch (first)
    //    {
    //    case 1:
    //    {
    //        deployBattleLine = "AlliedMelee";
    //        break;
    //    }
    //    case 2:
    //    {
    //        deployBattleLine = "AlliedRanged";
    //        break;
    //    }
    //    case 3:
    //    {
    //        deployBattleLine = "AlliedSiege";
    //        break;
    //    }
    //    case 4:
    //    {
    //        deployBattleLine = "EnemyMelee";
    //        break;
    //    }
    //    case 5:
    //    {
    //        deployBattleLine = "EnemyRanged";
    //        break;
    //    }
    //    case 6:
    //    {
    //        deployBattleLine = "EnemySiege";
    //        break;
    //    }
    //    default:break;
    //    }
    //
    //    deployIndex = second;
    QEventLoop eventLoop;

    QObject::connect(PlayingState, &GamePlayingState::ClickedOnEnemySiege, [&deployBattleLine, &eventLoop]
    {
      deployBattleLine = "EnemySiege";
      eventLoop.quit();
    });
    QObject::connect(PlayingState, &GamePlayingState::ClickedOnEnemyRanged, [&deployBattleLine, &eventLoop]
    {
      deployBattleLine = "EnemyRanged";
      eventLoop.quit();
    });
    QObject::connect(PlayingState, &GamePlayingState::ClickedOnEnemyMelee, [&deployBattleLine, &eventLoop]
    {
      deployBattleLine = "EnemyMelee";
      eventLoop.quit();
    });
    QObject::connect(PlayingState, &GamePlayingState::ClickedOnAlliedMelee, [&deployBattleLine, &eventLoop]
    {
      deployBattleLine = "AlliedMelee";
      eventLoop.quit();
    });
    QObject::connect(PlayingState, &GamePlayingState::ClickedOnAlliedRanged, [&deployBattleLine, &eventLoop]
    {
      deployBattleLine = "AlliedRanged";
      eventLoop.quit();
    });
    QObject::connect(PlayingState, &GamePlayingState::ClickedOnAlliedSiege, [&deployBattleLine, &eventLoop]
    {
      deployBattleLine = "AlliedSiege";
      eventLoop.quit();
    });

    eventLoop.exec();

    deployIndex = 0;
}


QString InteractingController::GetSelectedEffectDeployBattleLine()
{
    int choose;

    QEventLoop eventLoop;

    QObject::connect(PlayingState, &GamePlayingState::ClickedOnEnemySiege, [&choose, &eventLoop]
    {
      choose = 1;
      eventLoop.quit();
    });
    QObject::connect(PlayingState, &GamePlayingState::ClickedOnEnemyRanged, [&choose, &eventLoop]
    {
      choose = 2;
      eventLoop.quit();
    });
    QObject::connect(PlayingState, &GamePlayingState::ClickedOnEnemyMelee, [&choose, &eventLoop]
    {
      choose = 3;
      eventLoop.quit();
    });
    QObject::connect(PlayingState, &GamePlayingState::ClickedOnAlliedMelee, [&choose, &eventLoop]
    {
      choose = 4;
      eventLoop.quit();
    });
    QObject::connect(PlayingState, &GamePlayingState::ClickedOnAlliedRanged, [&choose, &eventLoop]
    {
      choose = 5;
      eventLoop.quit();
    });
    QObject::connect(PlayingState, &GamePlayingState::ClickedOnAlliedSiege, [&choose, &eventLoop]
    {
      choose = 6;
      eventLoop.quit();
    });

    eventLoop.exec();

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


void InteractingController::UpdateBattleFieldView()
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

        for (int i = 0; i < cards.size(); i++)
        {
            PlayingState->InsertCardToBattleLine(item, cards[i], i);
        }
    }
}


void InteractingController::SetPlayingState(GamePlayingState *PlayingState)
{
    InteractingController::PlayingState = PlayingState;
}

