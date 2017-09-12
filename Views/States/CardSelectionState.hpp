//
// Created on 2017/09/12 at 22:17.
//

#ifndef GWENT_CARDSELECTIONSTATE_HPP
#define GWENT_CARDSELECTIONSTATE_HPP

#include "IState.hpp"


class CardButton;


class QSignalMapper;

namespace Ui
{
class CardSelectionState;
}

class CardSelectionState : public QWidget, public IState
{
Q_OBJECT
public:
    CardSelectionState(QWidget *parent);

    QSignalMapper *SignalMapper;

    void SetAbdicable(bool abdicable);

    void ClearAllCards();
    void InsertCard(CardButton *cardButton);

    void RefreshMapper();

protected:
    Ui::CardSelectionState *CardSelectionStateUi;
signals:
    void ClickOnDoneButton();
};


#endif //GWENT_CARDSELECTIONSTATE_HPP
