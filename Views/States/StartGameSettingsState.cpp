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
}
