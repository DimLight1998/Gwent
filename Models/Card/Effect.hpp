//
// Created on 2017/09/03 at 15:43.
//

#ifndef GWENT_EFFECT_HPP
#define GWENT_EFFECT_HPP

#include "Card.hpp"
#include "Unit.hpp"
#include "../Containers/BattleLine.hpp"


class Effect : public Card
{
protected:
    Unit       *SelectedUnit; //!< used for effects unit select
    BattleLine *SelectedLine; //!< used for effects line select

public:
    Unit *GetSelectedUnit() const;
    void SetSelectedUnit(Unit *SelectedUnit);
    BattleLine *GetSelectedLine() const;
    void SetSelectedLine(BattleLine *SelectedLine);
};


#endif //GWENT_EFFECT_HPP
