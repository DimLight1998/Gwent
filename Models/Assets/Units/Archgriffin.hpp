//
// Created on 2017/09/05 at 16:48.
//

#ifndef GWENT_ARCHGRIFFIN_HPP
#define GWENT_ARCHGRIFFIN_HPP

#include "../../Card/Unit.hpp"


class Archgriffin : public Unit
{
public:
    Archgriffin(GameController *gameController);
    void OnDeploy() override;
};


#endif //GWENT_ARCHGRIFFIN_HPP
