//
// Created on 2017/09/04 at 09:57.
//

#ifndef GWENT_GERALTIGNI_HPP
#define GWENT_GERALTIGNI_HPP

#include "../../Card/Unit.hpp"


class GeraltIgni : public Unit
{
public:
    GeraltIgni(GameController *gameController);
    void OnDeploy() override;
    void OnDestroy() override;
};


#endif //GWENT_GERALTIGNI_HPP
