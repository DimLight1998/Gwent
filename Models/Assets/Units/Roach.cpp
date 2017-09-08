//
// Created on 2017/09/04 at 10:44.
//

#include "Roach.hpp"
#include "../../Meta/UnitMeta.hpp"


Roach::Roach(GameController *gameController)
    : Unit(gameController)
{
    CardMetaInfo = CardMeta::GetMetaByCardName("Roach");
    Power        = dynamic_cast<UnitMeta *>(CardMetaInfo)->GetInitialPower();
}
