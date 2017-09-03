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


void Unit::Gain(int gain)
{
    Power += gain;
}
