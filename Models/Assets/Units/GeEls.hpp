//
// Created on 2017/09/05 at 19:42.
//

#ifndef GWENT_GEELS_HPP
#define GWENT_GEELS_HPP

#include "../../Card/Unit.hpp"


class GeEls : public Unit
{
public:
    GeEls(GameController *gameController);
    void OnDeploy() override;
    void OnDestroy() override;
};


#endif //GWENT_GEELS_HPP
