//
// Created on 2017/09/03 at 16:15.
//

#include "BattleField.hpp"
#include "BattleSide.hpp"


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


CardContainer *BattleField::GetCardContainerByName(const QString& name)
{
    if (name.startsWith("Enemy"))
    {
        return EnemyBattleSide->GetCardContainerByName(name.mid(5));
    }

    if (name.startsWith("Allied"))
    {
        return AlliedBattleSide->GetCardContainerByName(name.mid(6));
    }

    throw 4583595;
}


QString BattleField::GetBattleLineContainingCard(int id)
{
    if (EnemyBattleSide->GetBattleLineByName("Melee")->IsBattleLineContainingCard(id))
    {
        return "EnemyMelee";
    }
    if (EnemyBattleSide->GetBattleLineByName("Ranged")->IsBattleLineContainingCard(id))
    {
        return "EnemyRanged";
    }
    if (EnemyBattleSide->GetBattleLineByName("Siege")->IsBattleLineContainingCard(id))
    {
        return "EnemySiege";
    }
    if (AlliedBattleSide->GetBattleLineByName("Melee")->IsBattleLineContainingCard(id))
    {
        return "AlliedMelee";
    }
    if (AlliedBattleSide->GetBattleLineByName("Melee")->IsBattleLineContainingCard(id))
    {
        return "AlliedRanged";
    }
    if (AlliedBattleSide->GetBattleLineByName("Melee")->IsBattleLineContainingCard(id))
    {
        return "AlliedSiege";
    }
}


bool BattleField::IsAContainer(const QString& name)
{
    QVector<QString> prefix  = {"Enemy", "Allied"};
    QVector<QString> postfix = {"Hand", "Deck", "Grave", "Discard"};

    for (const auto& i:prefix)
    {
        for (const auto& j:postfix)
        {
            if (name == i + j)
            {
                return true;
            }
        }
    }

    return false;
}


bool BattleField::IsABattleLine(const QString& name)
{
    QVector<QString> prefix  = {"Enemy", "Allied"};
    QVector<QString> postfix = {"Siege", "Ranged", "Melee"};

    for (const auto& i:prefix)
    {
        for (const auto& j:postfix)
        {
            if (name == i + j)
            {
                return true;
            }
        }
    }

    return false;
}
