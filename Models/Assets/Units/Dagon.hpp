//
// Created on 2017/09/05 at 15:36.
//

#ifndef GWENT_DAGON_HPP
#define GWENT_DAGON_HPP

#include "../../Card/Unit.hpp"


class Dagon : public Unit
{
public:
    Dagon();
    void OnDeploy() override;
};


#endif //GWENT_DAGON_HPP