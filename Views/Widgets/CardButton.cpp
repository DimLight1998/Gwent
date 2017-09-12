//
// Created on 2017/09/12 at 17:38.
//


#include <QPainter>
#include "CardButton.hpp"
#include "../../Models/Card/Unit.hpp"


CardButton::CardButton(QWidget *parent, int CardId, CardManager *Manager)
    : QPushButton(parent), CardId(CardId), Manager(Manager)
{
    auto pictureResourcePath = Manager->GetCardById(CardId)->GetCardMetaInfo()->GetPictureResourcePath();

    setStyleSheet("border-image: url(" + pictureResourcePath + ");");
    setFixedSize(62, 85);
}


int CardButton::GetCardId() const
{
    return CardId;
}


void CardButton::SetCardId(int CardId)
{
    CardButton::CardId = CardId;
}


CardManager *CardButton::GetManager() const
{
    return Manager;
}


void CardButton::SetManager(CardManager *Manager)
{
    CardButton::Manager = Manager;
}


void CardButton::paintEvent(QPaintEvent *event)
{
    QPushButton::paintEvent(event);

    QPainter painter(this);

    auto card = Manager->GetCardById(CardId);
    if (Unit::IsCardUnit(card))
    {
        QRect rect(0, 0, 30, 18);
        painter.setBrush(QBrush(QColor::fromRgb(255, 255, 255, 240)));
        painter.drawRect(rect);
        painter.drawText(rect, Qt::AlignCenter, QString::number(dynamic_cast<Unit *>(card)->GetPower()));
    }
}
