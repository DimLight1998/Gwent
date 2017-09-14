//
// Created on 2017/09/04 at 10:44.
//

#ifndef GWENT_ROACH_HPP
#define GWENT_ROACH_HPP

#include "../../Card/Unit.hpp"


class Roach : public Unit
{
public:
    Roach(GameController *gameController);
    void OnDestroy() override;
    void OnOtherCardDeployHandler(int cardId) override;
    void OnDeploy() override;
};


#endif //GWENT_ROACH_HPP
