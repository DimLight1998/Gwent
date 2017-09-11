//
// Created on 2017/09/11 at 15:32.
//

#include "BaseWindow.hpp"
#include "States/MainMenuState.hpp"
#include "States/CardGroupEditState.hpp"
#include "States/StartGameSettingsState.hpp"


BaseWindow::BaseWindow()
{
    StackedWidget = new QStackedWidget(this);
    setCentralWidget(StackedWidget);
    setMinimumSize(1280, 720);

    auto mainMenuState = new MainMenuState(StackedWidget);
    mainMenuState->SetBase(this);
    StackedWidget->addWidget(mainMenuState);

    auto cardGroupEditState = new CardGroupEditState(StackedWidget);
    cardGroupEditState->SetBase(this);
    StackedWidget->addWidget(cardGroupEditState);

    auto startGameSettingsState = new StartGameSettingsState(StackedWidget);
    startGameSettingsState->SetBase(this);
    StackedWidget->addWidget(startGameSettingsState);

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
}
