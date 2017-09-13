//
// Created on 2017/09/13 at 19:45.
//

#include "ResultState.hpp"
#include "ui_ResultState.h"


ResultState::ResultState(QWidget *parent)
    :
    QWidget(parent)
{
    ResultStateUi = new Ui::ResultState();
    ResultStateUi->setupUi(this);

    connect(ResultStateUi->pushButton, &QPushButton::clicked, [this]
    {
      Base->SwitchToState("MainMenu");
    });
}


void ResultState::SetResult(
    bool isWin,
    int allyRound1,
    int allyRound2,
    int allyRound3,
    int enemyRound1,
    int enemyRound2,
    int enemyRound3
)
{
    if (isWin)
    {
        ResultStateUi->label->setText("You Win!");
    }
    else
    {
        ResultStateUi->label->setText("You Lose!");
    }

    ResultStateUi->label_2->setText(QString("You: %1 | Oppenent: %2").arg(allyRound1, enemyRound1));
    ResultStateUi->label_3->setText(QString("You: %1 | Oppenent: %2").arg(allyRound2, enemyRound2));
    ResultStateUi->label_4->setText(QString("You: %1 | Oppenent: %2").arg(allyRound3, enemyRound3));
}


void ResultState::SetResult(
    bool isWin,
    int allyRound1,
    int allyRound2,
    int enemyRound1,
    int enemyRound2
)
{
    if (isWin)
    {
        ResultStateUi->label->setText("You Win!");
    }
    else
    {
        ResultStateUi->label->setText("You Lose!");
    }

    ResultStateUi->label_2->setText(QString("You: %1 | Oppenent: %2").arg(allyRound1, enemyRound1));
    ResultStateUi->label_3->setText(QString("You: %1 | Oppenent: %2").arg(allyRound2, enemyRound2));
    ResultStateUi->label_4->setText(QString(""));
}
