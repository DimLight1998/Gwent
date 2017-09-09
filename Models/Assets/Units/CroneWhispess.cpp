//
// Created on 2017/09/04 at 10:59.
//

#include "CroneWhispess.hpp"
#include "../../Meta/UnitMeta.hpp"


CroneWhispess::CroneWhispess(GameController *gameController)
    : Unit(gameController)
{
    CardMetaInfo = CardMeta::GetMetaByCardName("CroneWhispess");
    Power        = dynamic_cast<UnitMeta *>(CardMetaInfo)->GetInitialPower();
}


void CroneWhispess::OnDeploy()
{
    auto success = GlobalGameController->DeployCardFromContainerToBattleLine(
        "CroneBrewess", "AlliedDeck", SelectedLine, SelectedIndex + 1
    );

    GlobalGameController->DeployCardFromContainerToBattleLine(
        "CroneWeavess", "AlliedDeck", SelectedLine, SelectedIndex + (success ? 2 : 1)
    );
}
