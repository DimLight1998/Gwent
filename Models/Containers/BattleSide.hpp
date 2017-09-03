//
// Created on 2017/09/03 at 16:13.
//

#ifndef GWENT_BATTLESIDE_HPP
#define GWENT_BATTLESIDE_HPP

#include "BattleLine.hpp"
#include "CardContainer.hpp"


class CardContainer;
class BattleSide
{

protected:

    BattleLine    *MeleeLine;
    BattleLine    *RangedLine;
    BattleLine    *SiegeLine;
    CardContainer *HandCards;
    CardContainer *GraveCards;
    CardContainer *DeckCards;
    CardContainer *DiscardCards; ///< cards removed from game stores here

public:
    /// \brief get the battle line by name
    /// \param name name of the battle line, options: (Melee|Ranged|Siege)
    /// \return pointer to the battle field
    /// \note I use this for transmitting via network
    /// \throw 23458782 if name incorrect
    BattleLine *GetBattleLineByName(const QString& name) const;
};


#endif //GWENT_BATTLESIDE_HPP
