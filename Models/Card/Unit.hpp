//
// Created on 2017/09/03 at 15:38.
//

#ifndef GWENT_UNIT_HPP
#define GWENT_UNIT_HPP

#include "Card.hpp"


class Unit : public Card
{
public:
    void Damage(int damage);

protected:
    int  Power;
    int  Armor;
    int  TimeCount;
    bool HasShield;
};


#endif //GWENT_UNIT_HPP
