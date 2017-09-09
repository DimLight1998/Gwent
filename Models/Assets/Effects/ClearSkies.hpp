//
// Created on 2017/09/05 at 11:04.
//

#ifndef GWENT_CLEARSKIES_HPP
#define GWENT_CLEARSKIES_HPP

#include "../../Card/Effect.hpp"


class ClearSkies : public Effect
{
public:
    ClearSkies(GameController *gameController);
    void OnDeploy() override;
    void OnDestroy() override;
};


#endif //GWENT_CLEARSKIES_HPP
