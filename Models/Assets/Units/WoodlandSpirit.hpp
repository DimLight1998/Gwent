//
// Created on 2017/09/05 at 09:22.
//

#ifndef GWENT_WOODLANDSPIRIT_HPP
#define GWENT_WOODLANDSPIRIT_HPP

#include "../../Card/Unit.hpp"


class WoodlandSpirit : public Unit
{
public:
    WoodlandSpirit(GameController *gameController);
    void OnDeploy() override;
    void OnDestroy() override;
};


#endif //GWENT_WOODLANDSPIRIT_HPP
