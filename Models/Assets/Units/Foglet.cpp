//
// Created on 2017/09/03 at 21:55.
//

#include "Foglet.hpp"
#include "../../Meta/UnitMeta.hpp"


Foglet::Foglet(GameController *gameController)
    : Unit(gameController)
{
    CardMetaInfo = CardMeta::GetMetaByCardName("Foglet");
    Power        = dynamic_cast<UnitMeta *>(CardMetaInfo)->GetInitialPower();
}
