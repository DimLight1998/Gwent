//
// Created on 2017/09/03 at 16:15.
//

#ifndef GWENT_BATTLEFIELD_HPP
#define GWENT_BATTLEFIELD_HPP

#include "BattleLine.hpp"


class BattleSide;


class CardContainer;


/// \brief the class helps to get battle lines and containers
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

    /// \brief get the card container by name
    /// \param name name of the container, options: (Enemy|Allied)(Hand|Grave|Deck|Discard)
    /// \return pointer to the container
    /// \throw 4583595 if name incorrect
    CardContainer *GetCardContainerByName(const QString& name);

    /// \brief get the battle line containing a certain card
    /// \param id id of the card
    /// \return name of the battle line, "" if not found
    QString GetBattleLineContainingCard(int id);

    /// \brief get the container containing a certain card
    /// \param id id of the card
    /// \return name of the battle line, "" if not found
    QString getCardContainerContainingCard(int id);

    /// \brief judge if it is a container by the given name
    /// \param name name of the container/battle line in format
    /// (Enemy|Allied)(Hand|Grave|Deck|Discard|Melee|Ranged|Siege)
    /// \return true if its a container otherwise false
    static bool IsAContainer(const QString& name);

    /// \brief judge if it is a container by the given name
    /// \param name name of the container/battle line in format
    /// (Enemy|Allied)(Hand|Grave|Deck|Discard|Melee|Ranged|Siege)
    /// \return true if its a battle line otherwise false
    static bool IsABattleLine(const QString& name);
};


#endif //GWENT_BATTLEFIELD_HPP
