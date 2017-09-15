//
// Created on 2017/09/12 at 17:38.
//


#include <QPainter>
#include "CardButton.hpp"
#include "../../Models/Card/Unit.hpp"
#include "../../Models/Meta/UnitMeta.hpp"


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
    if (Unit::IsCardUnit(card) && IsVisibleToPlayer)
    {
        painter.setBrush(QBrush(QColor::fromRgb(255, 255, 255, 127)));

        QRect rectPower(0, 0, 30, 18);

        if (dynamic_cast<Unit *>(card)->IsHasShield())
        {
            painter.setBrush(QBrush(QColor::fromRgb(231, 190, 122, 255)));
            painter.drawRect(rectPower);
            painter.drawText(rectPower, Qt::AlignCenter, QString::number(dynamic_cast<Unit *>(card)->GetPower()));
            painter.setBrush(QBrush(QColor::fromRgb(255, 255, 255, 127)));
        }
        else
        {
            painter.drawRect(rectPower);
            painter.drawText(rectPower, Qt::AlignCenter, QString::number(dynamic_cast<Unit *>(card)->GetPower()));
        }

        QRect   locationRect(0, 18, 30, 18);
        QString locationString;
        switch (dynamic_cast<UnitMeta *>(card->GetCardMetaInfo())->GetDeployLocation())
        {
        case UnitMeta::DeployLocationEnum::Melee:
        {
            locationString = "M";
            break;
        }
        case UnitMeta::DeployLocationEnum::Ranged:
        {
            locationString = "R";
            break;
        }
        case UnitMeta::DeployLocationEnum::Siege:
        {
            locationString = "S";
            break;
        }
        case UnitMeta::DeployLocationEnum::Any:
        {
            locationString = "A";
            break;
        }
        }
        painter.drawRect(locationRect);
        painter.drawText(locationRect, Qt::AlignCenter, locationString);

        if (dynamic_cast<Unit *>(card)->GetArmor() > 0)
        {
            QRect rectArmor(0, 36, 30, 18);
            painter.drawRect(rectArmor);
            painter.drawText(rectArmor, Qt::AlignCenter,
                             "|" + QString::number(dynamic_cast<Unit *>(card)->GetArmor()));
        }

        if (dynamic_cast<Unit *>(card)->GetTimeCount() > 0)
        {
            QRect countDownPower(0, 54, 30, 18);
            painter.drawRect(countDownPower);
            painter.drawText(countDownPower, Qt::AlignCenter,
                             ":" + QString::number(dynamic_cast<Unit *>(card)->GetTimeCount()));
        }
    }
}


void CardButton::SetVisibleToPlayer(bool visible)
{
    IsVisibleToPlayer = visible;
    if (!visible)
    {
        setStyleSheet("border-image: url(:Resources/Back.png);");
    }
    else
    {
        auto pictureResourcePath = Manager->GetCardById(CardId)->GetCardMetaInfo()->GetPictureResourcePath();
        setStyleSheet("border-image: url(" + pictureResourcePath + ");");
    }
}
