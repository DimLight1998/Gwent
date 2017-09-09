//
// Created on 2017/09/04 at 10:48.
//

#ifndef GWENT_CRONEWEAVESS_HPP
#define GWENT_CRONEWEAVESS_HPP

#include "../../Card/Unit.hpp"


class CroneWeavess : public Unit
{
public:
    CroneWeavess(GameController *gameController);
    void OnDeploy() override;
    void OnDestroy() override;
};


#endif //GWENT_CRONEWEAVESS_HPP
