//
// Created on 2017/09/11 at 21:08.
//

#ifndef GWENT_MAINMENUSTATE_HPP
#define GWENT_MAINMENUSTATE_HPP

#include <QtWidgets/QWidget>
#include "IState.hpp"


namespace Ui
{
class MainMenuState;
}

class MainMenuState : public QWidget, public IState
{
Q_OBJECT
public:
    MainMenuState(QWidget *parent);
protected:
    Ui::MainMenuState *MainMenuStateUi;
};


#endif //GWENT_MAINMENUSTATE_HPP
