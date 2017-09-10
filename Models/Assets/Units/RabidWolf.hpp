//
// Created on 2017/09/04 at 16:23.
//

#ifndef GWENT_RABIDWOLF_HPP
#define GWENT_RABIDWOLF_HPP

#include "../../Card/Unit.hpp"


class RabidWolf : public Unit
{
public:
    RabidWolf(GameController *gameController);
    void OnDestroy() override;
};


#endif //GWENT_RABIDWOLF_HPP
