//
// Created on 2017/09/03 at 17:04.
//

#ifndef GWENT_FIRSTLIGHT_HPP
#define GWENT_FIRSTLIGHT_HPP

#include "../../Card/Effect.hpp"


class FirstLight : public Effect
{
public:
    FirstLight();

    void OnDeploy() override;
};


#endif //GWENT_FIRSTLIGHT_HPP
