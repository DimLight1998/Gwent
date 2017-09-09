//
// Created on 2017/09/03 at 23:01.
//

#ifndef GWENT_TORRENTIALRAIN_HPP
#define GWENT_TORRENTIALRAIN_HPP

#include "../../Card/Effect.hpp"


class TorrentialRain : public Effect
{
public:
    void OnDeploy() override;
    void OnDestroy() override;
    TorrentialRain(GameController *gameController);
};


#endif //GWENT_TORRENTIALRAIN_HPP
