//
// Created on 2017/09/05 at 09:45.
//

#include "CelaenoHarpy.hpp"


CelaenoHarpy::CelaenoHarpy()
{
    CardMetaInfo = CardMeta::GetMetaByCardName("CelaenoHarpy");
}


void CelaenoHarpy::OnDeploy()
{
    GlobalGameController->SpawnCard("HarpyEgg", SelectedLine, SelectedIndex);
    GlobalGameController->SpawnCard("HarpyEgg", SelectedLine, SelectedIndex);
}
