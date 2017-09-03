//
// Created on 2017/09/03 at 16:15.
//

#ifndef GWENT_BATTLEFIELD_HPP
#define GWENT_BATTLEFIELD_HPP

#include "BattleLine.hpp"
#include "BattleSide.hpp"


class BattleField
{
protected:
    BattleSide *EnemyBattleSide;
    BattleSide *AlliedBattleSide;

public:
    /// \brief get the battle line by name
    /// \param name name of the battle line, options: (Enemy|Allied)(Melee|Ranged|Siege)
    /// \return pointer to the battle field
    /// \note I use this for transmitting via network
    /// \throw 347853 if name incorrect
    BattleLine *GetBattleLineByName(const QString& name);
};


#endif //GWENT_BATTLEFIELD_HPP
