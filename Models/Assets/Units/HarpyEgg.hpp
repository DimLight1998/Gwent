//
// Created on 2017/09/04 at 15:08.
//

#ifndef GWENT_HARPYEGG_HPP
#define GWENT_HARPYEGG_HPP

#include "../../Card/Unit.hpp"


class HarpyEgg : public Unit
{
public:
    HarpyEgg(GameController *gameController);
    void OnDeathWish() override;
    void OnDestroy() override;
    int GetPowerUpWhenSwallowed() override;
};


#endif //GWENT_HARPYEGG_HPP
