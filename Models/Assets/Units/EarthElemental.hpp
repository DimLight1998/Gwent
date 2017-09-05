//
// Created on 2017/09/05 at 09:35.
//

#ifndef GWENT_EARTHELEMENTAL_HPP
#define GWENT_EARTHELEMENTAL_HPP

#include "../../Card/Unit.hpp"


class EarthElemental : public Unit
{
public:
    EarthElemental();
    void OnDeploy() override;
    void OnDeathWish() override;
};


#endif //GWENT_EARTHELEMENTAL_HPP
