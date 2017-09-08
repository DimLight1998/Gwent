//
// Created on 2017/09/04 at 00:27.
//

#ifndef GWENT_COMMANDERSHORN_HPP
#define GWENT_COMMANDERSHORN_HPP

#include "../../Card/Effect.hpp"


class CommandersHorn : public Effect
{
public:
    CommandersHorn(GameController *gameController);

    void OnDeploy() override;
};


#endif //GWENT_COMMANDERSHORN_HPP
