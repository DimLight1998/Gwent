//
// Created on 2017/09/04 at 10:41.
//

#ifndef GWENT_WILDHUNTRIDER_HPP
#define GWENT_WILDHUNTRIDER_HPP

#include "../../Card/Unit.hpp"


class WildHuntRider : public Unit
{
public:
    WildHuntRider(GameController *gameController);
    void OnDestroy() override;
    void OnDeploy() override;
};


#endif //GWENT_WILDHUNTRIDER_HPP
