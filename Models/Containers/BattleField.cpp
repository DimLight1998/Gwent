//
// Created on 2017/09/03 at 16:15.
//

#include "BattleField.hpp"


BattleLine *BattleField::GetBattleLineByName(const QString& name)
{
    if (name.startsWith("Enemy"))
    {
        return EnemyBattleSide->GetBattleLineByName(name.mid(5));
    }

    if (name.startsWith("Allied"))
    {
        return AlliedBattleSide->GetBattleLineByName(name.mid(6));
    }

    throw 347853;
}
