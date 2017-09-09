//
// Created on 2017/09/05 at 23:33.
//

#ifndef GWENT_VRANWARRIOR_HPP
#define GWENT_VRANWARRIOR_HPP

#include "../../Card/Unit.hpp"


class VranWarrior : public Unit
{
public:
    VranWarrior(GameController *gameController);
    void OnDeploy() override;
    void RoundUpdate() override;
    void OnDestroy() override;
protected:
    int CountDown;
};


#endif //GWENT_VRANWARRIOR_HPP
