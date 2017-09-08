//
// Created on 2017/09/04 at 15:11.
//

#include "HarpyHatchling.hpp"
#include "../../Meta/UnitMeta.hpp"


HarpyHatchling::HarpyHatchling()
{
    CardMetaInfo = CardMeta::GetMetaByCardName("HarpyHatchling");
    Power        = dynamic_cast<UnitMeta *>(CardMetaInfo)->GetInitialPower();
}
