//
// Created on 2017/09/12 at 16:38.
//

#include <QDebug>
#include "GamePlayingState.hpp"
#include "ui_GamePlayingState.h"
#include "../Widgets/CardButton.hpp"


GamePlayingState::GamePlayingState(QWidget *parent)
    :
    QWidget(parent)
{
    GamePlayingStateUi = new Ui::GamePlayingState();
    GamePlayingStateUi->setupUi(this);

    SignalMapper = new QSignalMapper(this);

    connect(GamePlayingStateUi->abdicateButton,
            &QPushButton::clicked,
            this,
            &GamePlayingState::ClickedOnAbdicateButton
    );

    GamePlayingStateUi->widget_5->installEventFilter(this);
    GamePlayingStateUi->widget->installEventFilter(this);
    GamePlayingStateUi->widget_4->installEventFilter(this);
    GamePlayingStateUi->widget_6->installEventFilter(this);
    GamePlayingStateUi->widget_7->installEventFilter(this);
    GamePlayingStateUi->widget_8->installEventFilter(this);
}


void GamePlayingState::StartGame()
{
    delete MainGameController;

    MainGameController = new GameController();

    CardGroup cardGroup;
    auto      fileName = Base->GetSharedData("SelectedCardGroupName").value<QString>();

    QFile file("./" + fileName + ".cg");
    file.open(QIODevice::ReadOnly);

    QTextStream in(&file);
    QString     cardGroupString;
    cardGroupString = in.readAll();

    file.close();

    cardGroup.UpdateFromString(cardGroupString);

    MainGameController->SetAllyCardGroup(cardGroup);
    MainGameController->SetAddressOfRemoteServer(Base->GetSharedData("ServerAddress").value<QString>());
    MainGameController->SetPortOfRemoteServer(static_cast<quint16>(Base->GetSharedData("ServerPort").value<int>()));
    MainGameController->GetInteracting()->SetPlayingState(this);

    try
    {
        MainGameController->StartGameEntry();
    }
    catch (...)
    {
    }
}


GamePlayingState::~GamePlayingState()
{
    delete MainGameController;
}


void GamePlayingState::ClearHand()
{
    QHBoxLayout *layout = nullptr;
    QLayoutItem *child;

    layout        = GamePlayingStateUi->horizontalLayout_3;
    while ((child = layout->takeAt(0)) != nullptr)
    {
        delete child->widget();
        delete child->spacerItem();
    }

    layout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Preferred));
    layout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Preferred));

    layout        = GamePlayingStateUi->horizontalLayout_13;
    while ((child = layout->takeAt(0)) != nullptr)
    {
        delete child->widget();
        delete child->spacerItem();
    }

    layout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Preferred));
    layout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Preferred));
}


void GamePlayingState::ClearBattleLine()
{
    for (const auto item:QVector<QHBoxLayout *>(
        {GamePlayingStateUi->horizontalLayout_2,
         GamePlayingStateUi->horizontalLayout_6,
         GamePlayingStateUi->horizontalLayout_4,
         GamePlayingStateUi->horizontalLayout_7,
         GamePlayingStateUi->horizontalLayout_9,
         GamePlayingStateUi->horizontalLayout_11
        }))
    {
        QLayoutItem *child;
        while ((child = item->takeAt(0)) != nullptr)
        {
            delete child->widget();
            delete child->spacerItem();
        }
    }

    EnemySiegeScoreIndicator   = new QPushButton(this);
    EnemyRangedScoreIndicator  = new QPushButton(this);
    EnemyMeleeScoreIndicator   = new QPushButton(this);
    AlliedSiegeScoreIndicator  = new QPushButton(this);
    AlliedRangedScoreIndicator = new QPushButton(this);
    AlliedMeleeScoreIndicator  = new QPushButton(this);

    EnemySiegeIndicator   = new QPushButton(tr("Siege"), this);
    EnemyRangedIndicator  = new QPushButton(tr("Ranged"), this);
    EnemyMeleeIndicator   = new QPushButton(tr("Melee"), this);
    AlliedSiegeIndicator  = new QPushButton(tr("Siege"), this);
    AlliedRangedIndicator = new QPushButton(tr("Ranged"), this);
    AlliedMeleeIndicator  = new QPushButton(tr("Melee"), this);

    EnemySiegeScoreIndicator->setEnabled(false);
    EnemyRangedScoreIndicator->setEnabled(false);
    EnemyMeleeScoreIndicator->setEnabled(false);
    AlliedSiegeScoreIndicator->setEnabled(false);
    AlliedRangedScoreIndicator->setEnabled(false);
    AlliedMeleeScoreIndicator->setEnabled(false);
    EnemySiegeIndicator->setEnabled(false);
    EnemyRangedIndicator->setEnabled(false);
    EnemyMeleeIndicator->setEnabled(false);
    AlliedSiegeIndicator->setEnabled(false);
    AlliedRangedIndicator->setEnabled(false);
    AlliedMeleeIndicator->setEnabled(false);

    GamePlayingStateUi->horizontalLayout_2->addWidget(EnemySiegeScoreIndicator);
    GamePlayingStateUi->horizontalLayout_2
        ->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Preferred));
    GamePlayingStateUi->horizontalLayout_2
        ->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Preferred));
    GamePlayingStateUi->horizontalLayout_2->addWidget(EnemySiegeIndicator);

    GamePlayingStateUi->horizontalLayout_6->addWidget(EnemyRangedScoreIndicator);
    GamePlayingStateUi->horizontalLayout_6
        ->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Preferred));
    GamePlayingStateUi->horizontalLayout_6
        ->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Preferred));
    GamePlayingStateUi->horizontalLayout_6->addWidget(EnemyRangedIndicator);

    GamePlayingStateUi->horizontalLayout_4->addWidget(EnemyMeleeScoreIndicator);
    GamePlayingStateUi->horizontalLayout_4
        ->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Preferred));
    GamePlayingStateUi->horizontalLayout_4
        ->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Preferred));
    GamePlayingStateUi->horizontalLayout_4->addWidget(EnemyMeleeIndicator);

    GamePlayingStateUi->horizontalLayout_7->addWidget(AlliedMeleeScoreIndicator);
    GamePlayingStateUi->horizontalLayout_7
        ->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Preferred));
    GamePlayingStateUi->horizontalLayout_7
        ->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Preferred));
    GamePlayingStateUi->horizontalLayout_7->addWidget(AlliedMeleeIndicator);

    GamePlayingStateUi->horizontalLayout_9->addWidget(AlliedRangedScoreIndicator);
    GamePlayingStateUi->horizontalLayout_9
        ->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Preferred));
    GamePlayingStateUi->horizontalLayout_9
        ->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Preferred));
    GamePlayingStateUi->horizontalLayout_9->addWidget(AlliedRangedIndicator);

    GamePlayingStateUi->horizontalLayout_11->addWidget(AlliedSiegeScoreIndicator);
    GamePlayingStateUi->horizontalLayout_11
        ->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Preferred));
    GamePlayingStateUi->horizontalLayout_11
        ->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Preferred));
    GamePlayingStateUi->horizontalLayout_11->addWidget(AlliedSiegeIndicator);
}


void GamePlayingState::InsertCardToHand(const QString& faction, int cardId, int index)
{
    auto cardButton = new CardButton(this, cardId, MainGameController->GetCardManager());
    if (faction == "Ally")
    {
        GamePlayingStateUi->horizontalLayout_13->insertWidget(index + 1, cardButton);
    }
    if (faction == "Enemy")
    {
        if (MainGameController->GetCardManager()->GetCardById(cardId)->GetCardMetaInfo()->GetCardType()
            != CardMeta::CardTypeEnum::Leader)
        {
            cardButton->SetVisibleToPlayer(false);
        }

        GamePlayingStateUi->horizontalLayout_3->insertWidget(index + 1, cardButton);
    }
}


void GamePlayingState::InsertCardToBattleLine(const QString& battleLineName, int cardId, int index)
{
    auto cardButton = new CardButton(this, cardId, MainGameController->GetCardManager());

    if (battleLineName == "EnemySiege")
    { GamePlayingStateUi->horizontalLayout_2->insertWidget(index + 2, cardButton); }
    if (battleLineName == "EnemyRanged")
    { GamePlayingStateUi->horizontalLayout_6->insertWidget(index + 2, cardButton); }
    if (battleLineName == "EnemyMelee")
    { GamePlayingStateUi->horizontalLayout_4->insertWidget(index + 2, cardButton); }
    if (battleLineName == "AlliedMelee")
    { GamePlayingStateUi->horizontalLayout_7->insertWidget(index + 2, cardButton); }
    if (battleLineName == "AlliedRanged")
    { GamePlayingStateUi->horizontalLayout_9->insertWidget(index + 2, cardButton); }
    if (battleLineName == "AlliedSiege")
    { GamePlayingStateUi->horizontalLayout_11->insertWidget(index + 2, cardButton); }
}


const QString& GamePlayingState::GetServerAddress() const
{
    return ServerAddress;
}


void GamePlayingState::SetServerAddress(const QString& ServerAddress)
{
    GamePlayingState::ServerAddress = ServerAddress;
}


quint16 GamePlayingState::GetServerPort() const
{
    return ServerPort;
}


void GamePlayingState::SetServerPort(quint16 ServerPort)
{
    GamePlayingState::ServerPort = ServerPort;
}


const QString& GamePlayingState::GetSelectedCardGroupName() const
{
    return SelectedCardGroupName;
}


void GamePlayingState::SetSelectedCardGroupName(const QString& SelectedCardGroupName)
{
    GamePlayingState::SelectedCardGroupName = SelectedCardGroupName;
}


bool GamePlayingState::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress)
    {
        if (watched == GamePlayingStateUi->widget_5)
        {
            auto mouseEvent = dynamic_cast<QMouseEvent *>(event);
            auto index      = GetIndexByMouseAndLayout(mouseEvent, GamePlayingStateUi->horizontalLayout_2);
            emit(ClickedOnEnemySiege(index));
        }
        if (watched == GamePlayingStateUi->widget)
        {
            auto mouseEvent = dynamic_cast<QMouseEvent *>(event);
            auto index      = GetIndexByMouseAndLayout(mouseEvent, GamePlayingStateUi->horizontalLayout_6);
            emit(ClickedOnEnemyRanged(index));
        }
        if (watched == GamePlayingStateUi->widget_4)
        {
            auto mouseEvent = dynamic_cast<QMouseEvent *>(event);
            auto index      = GetIndexByMouseAndLayout(mouseEvent, GamePlayingStateUi->horizontalLayout_4);
            emit(ClickedOnEnemyMelee(index));
        }
        if (watched == GamePlayingStateUi->widget_6)
        {
            auto mouseEvent = dynamic_cast<QMouseEvent *>(event);
            auto index      = GetIndexByMouseAndLayout(mouseEvent, GamePlayingStateUi->horizontalLayout_7);
            emit(ClickedOnAlliedMelee(index));
        }
        if (watched == GamePlayingStateUi->widget_7)
        {
            auto mouseEvent = dynamic_cast<QMouseEvent *>(event);
            auto index      = GetIndexByMouseAndLayout(mouseEvent, GamePlayingStateUi->horizontalLayout_9);
            emit(ClickedOnAlliedRanged(index));
        }
        if (watched == GamePlayingStateUi->widget_8)
        {
            auto mouseEvent = dynamic_cast<QMouseEvent *>(event);
            auto index      = GetIndexByMouseAndLayout(mouseEvent, GamePlayingStateUi->horizontalLayout_11);
            emit(ClickedOnAlliedSiege(index));
        }

        return false;
    }
    return false;
}


void GamePlayingState::RefreshCardsConnections()
{
    for (const auto layout:QVector<QHBoxLayout *>(
        {GamePlayingStateUi->horizontalLayout_2,
         GamePlayingStateUi->horizontalLayout_6,
         GamePlayingStateUi->horizontalLayout_4,
         GamePlayingStateUi->horizontalLayout_7,
         GamePlayingStateUi->horizontalLayout_9,
         GamePlayingStateUi->horizontalLayout_11
        }))
    {
        for (int i = 2; i < layout->count() - 2; i++)
        {
            auto button = layout->itemAt(i)->widget();

            connect(
                dynamic_cast<QPushButton *>(button),
                &QPushButton::clicked,
                SignalMapper,
                static_cast<void (QSignalMapper::*)()> (&QSignalMapper::map)
            );

            connect(dynamic_cast<QPushButton *>(button),
                    &QPushButton::clicked, []
                    { qDebug() << "Clicked"; });
            SignalMapper->setMapping(button, dynamic_cast<CardButton *>(button)->GetCardId());
        }
    }

    for (const auto layout:QVector<QHBoxLayout *>(
        {GamePlayingStateUi->horizontalLayout_3,
         GamePlayingStateUi->horizontalLayout_13
        }))
    {
        for (int i = 1; i < layout->count() - 1; i++)
        {
            auto button = layout->itemAt(i)->widget();

            connect(
                dynamic_cast<QPushButton *>(button),
                &QPushButton::clicked,
                SignalMapper,
                static_cast<void (QSignalMapper::*)()> (&QSignalMapper::map)
            );

            connect(dynamic_cast<QPushButton *>(button),
                    &QPushButton::clicked, []
                    { qDebug() << "Clicked"; });
            SignalMapper->setMapping(button, dynamic_cast<CardButton *>(button)->GetCardId());
        }
    }
}


GameController *GamePlayingState::GetMainGameController() const
{
    return MainGameController;
}


int GamePlayingState::GetIndexByMouseAndLayout(QMouseEvent *mouseEvent, QHBoxLayout *layout)
{
    auto x     = mouseEvent->pos().x();
    auto index = 0;

    for (int i = 2; i < layout->count() - 2; i++)
    {
        auto cardButton = layout->itemAt(i)->widget();
        if (x > cardButton->pos().x() + cardButton->size().width() / 2)
        {
            index++;
        }
    }

    return index;
}


void GamePlayingState::UpdateUi(
    const QVector<int>& battleLineScores,
    const QVector<QString>& battleLineWeathers,
    bool isAllyTurn)
{
    EnemySiegeScoreIndicator->setText(QString::number(battleLineScores[0]));
    EnemyRangedScoreIndicator->setText(QString::number(battleLineScores[1]));
    EnemyMeleeScoreIndicator->setText(QString::number(battleLineScores[2]));
    AlliedMeleeScoreIndicator->setText(QString::number(battleLineScores[3]));
    AlliedRangedScoreIndicator->setText(QString::number(battleLineScores[4]));
    AlliedSiegeScoreIndicator->setText(QString::number(battleLineScores[5]));

    auto widgets = QVector<QWidget *>(
        {
            GamePlayingStateUi->widget_5,
            GamePlayingStateUi->widget,
            GamePlayingStateUi->widget_4,
            GamePlayingStateUi->widget_6,
            GamePlayingStateUi->widget_7,
            GamePlayingStateUi->widget_8,
        }
    );

    GamePlayingStateUi->label->setText(
        QString::number(battleLineScores[0] + battleLineScores[1] + battleLineScores[2])
    );

    GamePlayingStateUi->label_2->setText(
        QString::number(battleLineScores[3] + battleLineScores[4] + battleLineScores[5])
    );

    for (int i = 0; i < widgets.size(); i++)
    {
        if (battleLineWeathers[i] == "Rain")
        {
            widgets[i]->setStyleSheet("background-color: rgba(0, 85, 100, 100);");
        }
        if (battleLineWeathers[i] == "Frost")
        {
            widgets[i]->setStyleSheet("background-color: rgba(0, 85, 200, 100);");
        }
        if (battleLineWeathers[i] == "Fog")
        {
            widgets[i]->setStyleSheet("background-color: rgba(57, 125, 84, 120);");
        }
        if (battleLineWeathers[i] == "None")
        {
            widgets[i]->setStyleSheet("background-color: rgb(0, 0, 0, 0);");
        }
    }

    if (isAllyTurn)
    {
        GamePlayingStateUi->abdicateButton->setText(tr("Your turn\n\nPress here to pass"));
        GamePlayingStateUi->abdicateButton->setStyleSheet("background-color: rgb(0, 118, 177);");
    }
    else
    {
        GamePlayingStateUi->abdicateButton->setText(tr("Your opponent's turn\n\nPlease wait..."));
        GamePlayingStateUi->abdicateButton->setStyleSheet("background-color: rgb(140, 0, 2);");
    }
}
