//
// Created on 2017/09/12 at 22:17.
//

#include "CardSelectionState.hpp"
#include "ui_CardSelectionState.h"
#include "../Widgets/CardButton.hpp"
#include <QSignalMapper>


CardSelectionState::CardSelectionState(QWidget *parent)
    :
    QWidget(parent)
{
    CardSelectionStateUi = new Ui::CardSelectionState();
    CardSelectionStateUi->setupUi(this);

    SignalMapper = new QSignalMapper(this);
    connect(CardSelectionStateUi->pushButton, &QPushButton::clicked, this, &CardSelectionState::ClickOnDoneButton);
}


void CardSelectionState::SetAbdicable(bool abdicable)
{
    CardSelectionStateUi->pushButton->setEnabled(abdicable);
}


void CardSelectionState::ClearAllCards()
{
    QLayoutItem *child;
    while ((child = CardSelectionStateUi->horizontalLayout->takeAt(0)) != nullptr)
    { }
}


void CardSelectionState::InsertCard(CardButton *cardButton)
{
    CardSelectionStateUi->horizontalLayout->insertWidget(-1, cardButton);
}


void CardSelectionState::RefreshMapper()
{
    SignalMapper->disconnect();

    for (int i = 0; i < CardSelectionStateUi->horizontalLayout->count(); i++)
    {
        auto cardButton = dynamic_cast<CardButton *>(CardSelectionStateUi->horizontalLayout->itemAt(i)->widget());

        connect(
            cardButton,
            &CardButton::clicked,
            SignalMapper,
            static_cast<void (QSignalMapper::*)()>(&QSignalMapper::map)
        );

        SignalMapper->setMapping(cardButton, cardButton->GetCardId());
    }
}
