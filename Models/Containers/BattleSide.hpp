//
// Created on 2017/09/03 at 16:13.
//

#ifndef GWENT_BATTLESIDE_HPP
#define GWENT_BATTLESIDE_HPP

#include "BattleLine.hpp"
#include "CardContainer.hpp"


class BattleSide
{
protected:
    BattleLine    *MeleeLine;
    BattleLine    *RangedLine;
    BattleLine    *SiegeLine;
    CardContainer *HandCards;
    CardContainer *GraveCards;
    CardContainer *DeckCards;
};


#endif //GWENT_BATTLESIDE_HPP
