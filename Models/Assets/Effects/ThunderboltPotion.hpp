//
// Created on 2017/09/04 at 09:28.
//

#ifndef GWENT_THUNDERBOLTPOTION_HPP
#define GWENT_THUNDERBOLTPOTION_HPP

#include "../../Card/Effect.hpp"


class ThunderboltPotion : public Effect
{
public:
    ThunderboltPotion(GameController *gameController);
    void OnDeploy() override;
};


#endif //GWENT_THUNDERBOLTPOTION_HPP
