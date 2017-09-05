//
// Created on 2017/09/05 at 19:27.
//

#ifndef GWENT_FRIGHTENER_HPP
#define GWENT_FRIGHTENER_HPP

#include "../../Card/Unit.hpp"


class Frightener : public Unit
{
public:
    Frightener();
    void OnDeploy() override;
};


#endif //GWENT_FRIGHTENER_HPP
