//
// Created on 2017/09/04 at 11:01.
//

#ifndef GWENT_ARACHAS_HPP
#define GWENT_ARACHAS_HPP

#include "../../Card/Unit.hpp"


class Arachas : public Unit
{
public:
    Arachas(GameController *gameController);
    void OnDeploy() override;
    void OnDestroy() override;
};


#endif //GWENT_ARACHAS_HPP
