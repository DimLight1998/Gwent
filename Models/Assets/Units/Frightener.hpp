//
// Created on 2017/09/05 at 19:27.
//

#ifndef GWENT_FRIGHTENER_HPP
#define GWENT_FRIGHTENER_HPP

#include "../../Card/Unit.hpp"


class Frightener : public Unit
{
public:
    Frightener(GameController *gameController);
    void OnDeploy() override;
    void OnDestroy() override;
};


#endif //GWENT_FRIGHTENER_HPP
