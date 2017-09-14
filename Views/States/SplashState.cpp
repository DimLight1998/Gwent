//
// Created on 2017/09/14 at 20:19.
//

#include <QtCore/QPropertyAnimation>
#include <QtCore/QTimer>
#include "SplashState.hpp"
#include "ui_SplashState.h"


void SplashState::RestartAnimation()
{
    SplashStateUi->label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    SplashStateUi->label->setAlignment(Qt::AlignCenter);

    auto animation = new QPropertyAnimation(SplashStateUi->label, "geometry");
    animation->setDuration(1600);
    animation->setStartValue(QRect(0, 0, 1280, 300));
    animation->setKeyValueAt(0.5, QRect(0, 0, 1280, 750));
    animation->setEndValue(QRect(0, 0, 1280, 750));
    animation->setEasingCurve(QEasingCurve::Linear);
    animation->start();

    QTimer::singleShot(8000, animation, &QPropertyAnimation::deleteLater);
    connect(animation, &QPropertyAnimation::finished, [this]
    {
      SplashStateUi->label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
      SplashStateUi->label->setFixedSize(1280, 750);
      Base->SwitchToState("MainMenu");
    });
}


SplashState::SplashState(QWidget *parent)
    : QWidget(parent), SplashStateUi(new Ui::SplashState)
{
    SplashStateUi->setupUi(this);
}
