//
// Created on 2017/09/11 at 15:32.
//

#include <QApplication>
#include "BaseWindow.hpp"
#include "States/MainMenuState.hpp"
#include "States/CardGroupEditState.hpp"
#include "States/StartGameSettingsState.hpp"
#include "States/GamePlayingState.hpp"
#include "States/CardSelectionState.hpp"
#include "States/ResultState.hpp"


BaseWindow::BaseWindow()
{
    StackedWidget = new QStackedWidget(this);
    setCentralWidget(StackedWidget);
    setMinimumSize(1280, 750);

    auto mainMenuState = new MainMenuState(StackedWidget);
    mainMenuState->SetBase(this);
    StackedWidget->addWidget(mainMenuState);
    SetSharedData("MainMenuState", QVariant::fromValue(mainMenuState));

    auto cardGroupEditState = new CardGroupEditState(StackedWidget);
    cardGroupEditState->SetBase(this);
    StackedWidget->addWidget(cardGroupEditState);
    SetSharedData("CardGroupEditState", QVariant::fromValue(cardGroupEditState));

    auto startGameSettingsState = new StartGameSettingsState(StackedWidget);
    startGameSettingsState->SetBase(this);
    StackedWidget->addWidget(startGameSettingsState);
    SetSharedData("StartGameSettingsState", QVariant::fromValue(startGameSettingsState));

    auto gamePlayingState = new GamePlayingState(StackedWidget);
    gamePlayingState->SetBase(this);
    StackedWidget->addWidget(gamePlayingState);
    SetSharedData("GamePlayingState", QVariant::fromValue(gamePlayingState));

    auto cardSelectionState = new CardSelectionState(StackedWidget);
    cardSelectionState->SetBase(this);
    StackedWidget->addWidget(cardSelectionState);
    SetSharedData("CardSelectionState", QVariant::fromValue(cardSelectionState));

    auto resultState = new ResultState(StackedWidget);
    resultState->SetBase(this);
    StackedWidget->addWidget(resultState);
    SetSharedData("ResultState", QVariant::fromValue(resultState));

    SwitchToState("MainMenu");
}


QStackedWidget *BaseWindow::GetStackedWidget() const
{
    return StackedWidget;
}


void BaseWindow::SwitchToState(const QString& stateName)
{
    if (stateName == "MainMenu")
    {
        StackedWidget->setCurrentIndex(0);
    }

    if (stateName == "CardGroupEdit")
    {
        StackedWidget->setCurrentIndex(1);
    }

    if (stateName == "StartGameSettings")
    {
        StackedWidget->setCurrentIndex(2);
    }

    if (stateName == "GamePlayingStart")
    {
        StackedWidget->setCurrentIndex(3);
        dynamic_cast<GamePlayingState *>(StackedWidget->currentWidget())->StartGame();
    }

    if (stateName == "GamePlaying")
    {
        StackedWidget->setCurrentIndex(3);
    }

    if (stateName == "CardSelection")
    {
        StackedWidget->setCurrentIndex(4);
    }

    if (stateName == "Result")
    {
        StackedWidget->setCurrentIndex(5);
    }
}


QVariant BaseWindow::GetSharedData(const QString& index)
{
    return SharedData[index];
}


void BaseWindow::SetSharedData(const QString& index, QVariant data)
{
    SharedData.insert(index, data);
}


void BaseWindow::closeEvent(QCloseEvent *event)
{
    QApplication::exit(0);
}
