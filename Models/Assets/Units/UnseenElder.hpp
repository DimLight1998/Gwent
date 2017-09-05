//
// Created on 2017/09/06 at 01:20.
//

#ifndef GWENT_UNSEENELDER_HPP
#define GWENT_UNSEENELDER_HPP

#include "../../Card/Unit.hpp"


class UnseenElder : public Unit
{
public:
    UnseenElder();
    void OnDeploy() override;
};


#endif //GWENT_UNSEENELDER_HPP
