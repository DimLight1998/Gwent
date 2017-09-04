//
// Created on 2017/09/04 at 22:37.
//

#ifndef GWENT_ARACHASHATCHLING_HPP
#define GWENT_ARACHASHATCHLING_HPP

#include "../../Card/Unit.hpp"


class ArachasHatchling : public Unit
{
public:
    ArachasHatchling();
    void OnDeploy() override;
};


#endif //GWENT_ARACHASHATCHLING_HPP
