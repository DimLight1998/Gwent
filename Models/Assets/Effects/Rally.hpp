//
// Created on 2017/09/05 at 11:04.
//

#ifndef GWENT_RALLY_HPP
#define GWENT_RALLY_HPP

#include "../../Card/Effect.hpp"


class Rally : public Effect
{
public:
    Rally();
    void OnDeploy() override;
};


#endif //GWENT_RALLY_HPP
