//
// Created on 2017/09/05 at 09:45.
//

#include "CelaenoHarpy.hpp"
#include "../../Meta/UnitMeta.hpp"


CelaenoHarpy::CelaenoHarpy(GameController *gameController)
    : Unit(gameController)
{
    CardMetaInfo = CardMeta::GetMetaByCardName("CelaenoHarpy");
    Power        = dynamic_cast<UnitMeta *>(CardMetaInfo)->GetInitialPower();
}


void CelaenoHarpy::OnDeploy()
{
    GlobalGameController->SpawnCard("HarpyEgg", SelectedLine, SelectedIndex);
    GlobalGameController->SpawnCard("HarpyEgg", SelectedLine, SelectedIndex);
}
