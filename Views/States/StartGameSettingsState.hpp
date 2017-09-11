//
// Created on 2017/09/11 at 22:28.
//

#ifndef GWENT_STARTGAMESETTINGSSTATE_HPP
#define GWENT_STARTGAMESETTINGSSTATE_HPP

#include <QtWidgets/QWidget>
#include "IState.hpp"


namespace Ui
{
class StartGameSettingsState;
}

class StartGameSettingsState : public QWidget, public IState
{
Q_OBJECT
public:;
    StartGameSettingsState(QWidget *parent);
protected:
    Ui::StartGameSettingsState *StartGameSettingsStateUi;
};


#endif //GWENT_STARTGAMESETTINGSSTATE_HPP
