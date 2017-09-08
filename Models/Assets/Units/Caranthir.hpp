//
// Created on 2017/09/05 at 16:15.
//

#ifndef GWENT_CARANTHIR_HPP
#define GWENT_CARANTHIR_HPP

#include "../../Card/Unit.hpp"


class Caranthir : public Unit
{
public:
    Caranthir(GameController *gameController);
    void OnDeploy() override;
};


#endif //GWENT_CARANTHIR_HPP
