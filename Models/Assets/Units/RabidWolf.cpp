//
// Created on 2017/09/04 at 16:23.
//

#include "RabidWolf.hpp"
#include "../../Meta/UnitMeta.hpp"


RabidWolf::RabidWolf()
{
    CardMetaInfo = CardMeta::GetMetaByCardName("RabidWolf");
    Power        = dynamic_cast<UnitMeta *>(CardMetaInfo)->GetInitialPower();
}
