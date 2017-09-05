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
