//
// Created on 2017/09/13 at 19:45.
//

#ifndef GWENT_RESULTSTATE_HPP
#define GWENT_RESULTSTATE_HPP

#include <QtWidgets/QWidget>
#include "IState.hpp"


namespace Ui
{
class ResultState;
}

class ResultState : public QWidget, public IState
{
Q_OBJECT
public:
    ResultState(QWidget *parent);

    void SetResult(
        const QString& text,
        int allyRound1,
        int allyRound2,
        int allyRound3,
        int enemyRound1,
        int enemyRound2,
        int enemyRound3
    );

    void SetResult(
        const QString& text,
        int allyRound1,
        int allyRound2,
        int enemyRound1,
        int enemyRound2
    );
protected:
    Ui::ResultState *ResultStateUi;
};


#endif //GWENT_RESULTSTATE_HPP
