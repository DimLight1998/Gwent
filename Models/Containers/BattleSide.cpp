//
// Created on 2017/09/03 at 16:13.
//

#include "BattleSide.hpp"
#include <QDateTime>


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


BattleSide::BattleSide()
{
    MeleeLine    = new BattleLine();
    RangedLine   = new BattleLine();
    SiegeLine    = new BattleLine();
    HandCards    = new CardContainer();
    GraveCards   = new CardContainer();
    DeckCards    = new CardContainer();
    DiscardCards = new CardContainer();
}


BattleSide::~BattleSide()
{
    delete MeleeLine;
    delete RangedLine;
    delete SiegeLine;
    delete HandCards;
    delete GraveCards;
    delete DeckCards;
    delete DiscardCards;
}

