//
// Created on 2017/09/04 at 10:59.
//

#ifndef GWENT_CRONEWHISPESS_HPP
#define GWENT_CRONEWHISPESS_HPP

#include "../../Card/Unit.hpp"


class CroneWhispess : public Unit
{
public:
    CroneWhispess();
    void OnDeploy() override;
};


#endif //GWENT_CRONEWHISPESS_HPP
