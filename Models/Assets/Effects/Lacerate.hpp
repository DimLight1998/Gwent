//
// Created on 2017/09/03 at 23:29.
//

#ifndef GWENT_LACERATE_HPP
#define GWENT_LACERATE_HPP

#include "../../Card/Effect.hpp"


class Lacerate : public Effect
{
public:
    Lacerate(GameController *gameController);
    void OnDeploy() override;
};


#endif //GWENT_LACERATE_HPP
