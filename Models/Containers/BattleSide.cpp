//
// Created on 2017/09/03 at 16:13.
//

#include "BattleSide.hpp"


BattleLine *BattleSide::GetBattleLineByName(const QString& name) const
{
    if (name == "Melee")
    {
        return MeleeLine;
    }

    if (name == "Ranged")
    {
        return RangedLine;
    }

    if (name == "Siege")
    {
        return SiegeLine;
    }

    throw 23458782;
}
