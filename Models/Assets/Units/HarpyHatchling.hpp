//
// Created on 2017/09/04 at 15:11.
//

#ifndef GWENT_HARPYHATCHLING_HPP
#define GWENT_HARPYHATCHLING_HPP

#include "../../Card/Unit.hpp"


class HarpyHatchling : public Unit
{
public:
    HarpyHatchling(GameController *gameController);
    void OnDestroy() override;
};


#endif //GWENT_HARPYHATCHLING_HPP
