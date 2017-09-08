//
// Created on 2017/09/04 at 10:56.
//

#include "CroneBrewess.hpp"
#include "../../Meta/UnitMeta.hpp"


CroneBrewess::CroneBrewess(GameController *gameController)
    : Unit(gameController)
{
    CardMetaInfo = CardMeta::GetMetaByCardName("CroneBrewess");
    Power        = dynamic_cast<UnitMeta *>(CardMetaInfo)->GetInitialPower();
}


void CroneBrewess::OnDeploy()
{
    GlobalGameController->DeployCardFromContainerToBattleLine(
        "CroneWeavess", "AlliedDeck", SelectedLine, SelectedIndex + 1
    );

    GlobalGameController->DeployCardFromContainerToBattleLine(
        "CroneWhispess", "AlliedDeck", SelectedLine, SelectedIndex + 2
    );
}
