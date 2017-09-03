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


CardContainer *BattleSide::GetCardContainerByName(const QString& name) const
{
    if (name == "Hand")
    {
        return HandCards;
    }
    if (name == "Grave")
    {
        return GraveCards;
    }
    if (name == "Deck")
    {
        return DeckCards;
    }
    if (name == "Discard")
    {
        return DiscardCards;
    }

    throw 23423425;
}
