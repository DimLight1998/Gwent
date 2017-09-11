//
// Created on 2017/09/03 at 17:40.
//

#ifndef GWENT_BITINGFROST_HPP
#define GWENT_BITINGFROST_HPP

#include "../../Card/Effect.hpp"


class BitingFrost : public Effect
{
public:
    BitingFrost(GameController *gameController);

    void OnDeploy() override;
    void OnDestroy() override;

    static void ExecuteDamage(GameController *gameController, const QString& battleLineName);
};


#endif //GWENT_BITINGFROST_HPP
