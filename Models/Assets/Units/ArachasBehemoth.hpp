//
// Created on 2017/09/06 at 01:01.
//

#ifndef GWENT_ARACHASBEHEMOTH_HPP
#define GWENT_ARACHASBEHEMOTH_HPP

#include "../../Card/Unit.hpp"


class ArachasBehemoth : public Unit
{
public:
    ArachasBehemoth(GameController *gameController);
    void OnDeploy() override;
};


#endif //GWENT_ARACHASBEHEMOTH_HPP
