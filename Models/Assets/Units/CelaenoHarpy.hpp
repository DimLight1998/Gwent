//
// Created on 2017/09/05 at 09:45.
//

#ifndef GWENT_CELAENOHARPY_HPP
#define GWENT_CELAENOHARPY_HPP

#include "../../Card/Unit.hpp"


class CelaenoHarpy : public Unit
{
public:
    CelaenoHarpy();
    void OnDeploy() override;
};


#endif //GWENT_CELAENOHARPY_HPP
