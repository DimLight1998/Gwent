//
// Created on 2017/09/11 at 21:08.
//

#include <QtCore/QTranslator>
#include "MainMenuState.hpp"
#include "ui_MainMenuState.h"


MainMenuState::MainMenuState(QWidget *parent)
    :
    QWidget(parent)
{
    MainMenuStateUi = new Ui::MainMenuState();
    MainMenuStateUi->setupUi(this);

    connect(MainMenuStateUi->pushButton_4, &QPushButton::clicked, [this]
    {
      Base->SwitchToState("CardGroupEdit");
    });

    connect(MainMenuStateUi->pushButton_6, &QPushButton::clicked, []
    {
      QApplication::exit(0);
    });

    connect(MainMenuStateUi->pushButton, &QPushButton::clicked, [this]
    {
      Base->SwitchToState("StartGameSettings");
    });
}
