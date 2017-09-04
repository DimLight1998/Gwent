//
// Created on 2017/09/04 at 09:00.
//

#ifndef GWENT_BEKKERSTWISTEDMIRROR_HPP
#define GWENT_BEKKERSTWISTEDMIRROR_HPP

#include "../../Card/Effect.hpp"


class BekkersTwistedMirror : public Effect
{
public:
    BekkersTwistedMirror();
    void OnDeploy() override;
};


#endif //GWENT_BEKKERSTWISTEDMIRROR_HPP
