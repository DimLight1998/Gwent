//
// Created on 2017/09/03 at 15:38.
//

#ifndef GWENT_UNIT_HPP
#define GWENT_UNIT_HPP

#include "Card.hpp"


class Unit : public Card
{
public:
    /// \brief damage the unit, OnDestory will be called if the unit is dead
    /// \param damage the damage
    void Damage(int damage);

    /// \brief increase the unit's power
    /// \param gain the point of the gain
    void Gain(int gain);

protected:
    int  Power;
    int  Armor;
    int  TimeCount;
    bool HasShield;

    QString SelectedLine;
    int     SelectedIndex;
};


#endif //GWENT_UNIT_HPP
