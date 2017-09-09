//
// Created on 2017/09/03 at 21:52.
//

#ifndef GWENT_IMPENETRABLEFOG_HPP
#define GWENT_IMPENETRABLEFOG_HPP

#include "../../Card/Effect.hpp"


class ImpenetrableFog : public Effect
{
public:
    ImpenetrableFog(GameController *gameController);

    void OnDeploy() override;
    void OnDestroy() override;
};


#endif //GWENT_IMPENETRABLEFOG_HPP
