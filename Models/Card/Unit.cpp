//
// Created on 2017/09/03 at 15:38.
//

#include "Unit.hpp"


void Unit::Damage(int damage)
{
    // if the unit has a shield, the shield will be broken and there is no harm
    if (HasShield)
    {
        HasShield = false;
        return;
    }

    // if the unit has armor, damage armor first
    // if the unit doesn't have armor, the code below works too
    if (damage <= Armor)
    {
        Armor -= damage;
    }
    else
    {
        damage -= Armor;
        Armor = 0;
        Power -= damage;
    }

    // if the unit is killed, call OnDestroyed()
    if (Power <= 0)
    {
        OnDestroy();
    }
}


void Unit::GainPower(int gain)
{
    Power += gain;
}


void Unit::DamageIgnoringArmorAndShield(int damage)
{
    Power -= damage;

    if (Power <= 0)
    {
        OnDestroy();
    }
}


int Unit::GetPower() const
{
    return Power;
}


void Unit::SetPower(int Power)
{
    Unit::Power = Power;
}


int Unit::GetArmor() const
{
    return Armor;
}


void Unit::SetArmor(int Armor)
{
    Unit::Armor = Armor;
}


int Unit::GetTimeCount() const
{
    return TimeCount;
}


void Unit::SetTimeCount(int TimeCount)
{
    Unit::TimeCount = TimeCount;
}


bool Unit::IsHasShield() const
{
    return HasShield;
}


void Unit::SetHasShield(bool HasShield)
{
    Unit::HasShield = HasShield;
}


void Unit::GainArmor(int gain)
{
    Armor += gain;
}


void Unit::Destroy()
{
    HasShield = false;
    Armor     = 0;
    Power     = 0;
    OnDestroy();
}


bool Unit::IsCardUnit(Card *card)
{
    return (dynamic_cast<Unit *>(card) != nullptr);
}


const QString& Unit::GetSelectedLine() const
{
    return SelectedLine;
}


void Unit::SetSelectedLine(const QString& SelectedLine)
{
    Unit::SelectedLine = SelectedLine;
}


int Unit::GetSelectedIndex() const
{
    return SelectedIndex;
}


void Unit::SetSelectedIndex(int SelectedIndex)
{
    Unit::SelectedIndex = SelectedIndex;
}


QString Unit::ToDisplayableString()
{
    return QString("[%1] %2 (Power %3) (Armor %4) (CD %5) (Shield %6)")
        .arg(CardId)
        .arg(CardMetaInfo->GetName())
        .arg(GetPower())
        .arg(GetArmor())
        .arg(GetTimeCount())
        .arg(IsHasShield() ? "On" : "Off");
}


QString Unit::ToString()
{
    return QString("%1_%2_%3_%4_%5_%6")
        .arg(CardId)
        .arg(CardMetaInfo->GetName())
        .arg(GetPower())
        .arg(GetArmor())
        .arg(GetTimeCount())
        .arg(IsHasShield() ? "1" : "0");
}


Unit::Unit(GameController *gameController)
    : Card(gameController)
{ }


void Unit::UpdateFromString(const QString& source)
{
    auto list = source.split('_', QString::SkipEmptyParts);
    SetCardId(list[0].toInt());
    SetPower(list[2].toInt());
    SetArmor(list[3].toInt());
    SetTimeCount(list[4].toInt());
    SetHasShield(list[5] == "1");
}


int Unit::GetPowerUpWhenSwallowed()
{
    return Power;
}
