//
// Created on 2017/09/14 at 20:19.
//

#ifndef GWENT_SPLASHSTATE_HPP
#define GWENT_SPLASHSTATE_HPP

#include "IState.hpp"


namespace Ui
{
class SplashState;
}

class SplashState : public QWidget, public IState
{
Q_OBJECT
public:
    SplashState(QWidget *parent);
    void RestartAnimation();
private:
    Ui::SplashState *SplashStateUi;
};


#endif //GWENT_SPLASHSTATE_HPP
