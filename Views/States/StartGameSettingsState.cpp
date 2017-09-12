//
// Created on 2017/09/11 at 22:28.
//

#include "StartGameSettingsState.hpp"
#include "ui_StartGameSettingsState.h"


StartGameSettingsState::StartGameSettingsState(QWidget *parent)
    :
    QWidget(parent)
{
    StartGameSettingsStateUi = new Ui::StartGameSettingsState();
    StartGameSettingsStateUi->setupUi(this);

    connect(StartGameSettingsStateUi->pushButton_2, &QPushButton::clicked, [this]
    {
      Base->SwitchToState("MainMenu");
    });

    connect(StartGameSettingsStateUi->pushButton, &QPushButton::clicked, [this]
    {
      Base->SetSharedData("ServerAddress", QVariant::fromValue(StartGameSettingsStateUi->lineEdit->text()));
      Base->SetSharedData("ServerPort", QVariant::fromValue(StartGameSettingsStateUi->lineEdit_2->text().toInt()));
      Base->SetSharedData("SelectedCardGroupName", QVariant::fromValue(StartGameSettingsStateUi->comboBox
                                                                           ->currentText()));

      Base->SwitchToState("GamePlayingStart");
    });
}