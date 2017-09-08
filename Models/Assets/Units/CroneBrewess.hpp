//
// Created on 2017/09/04 at 10:56.
//

#ifndef GWENT_CRONEBREWESS_HPP
#define GWENT_CRONEBREWESS_HPP

#include "../../Card/Unit.hpp"


class CroneBrewess : public Unit
{
public:
    CroneBrewess(GameController *gameController);
    void OnDeploy() override;
};


#endif //GWENT_CRONEBREWESS_HPP
