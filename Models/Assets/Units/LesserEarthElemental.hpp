//
// Created on 2017/09/04 at 22:36.
//

#ifndef GWENT_LESSEREARTHELEMENTAL_HPP
#define GWENT_LESSEREARTHELEMENTAL_HPP

#include "../../Card/Unit.hpp"


class LesserEarthElemental : public Unit
{
public:
    LesserEarthElemental(GameController *gameController);
    void OnDestroy() override;
};


#endif //GWENT_LESSEREARTHELEMENTAL_HPP
