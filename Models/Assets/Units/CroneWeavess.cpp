//
// Created on 2017/09/04 at 10:48.
//

#include "CroneWeavess.hpp"
#include "../../Meta/UnitMeta.hpp"


CroneWeavess::CroneWeavess(GameController *gameController)
    : Unit(gameController)
{
    CardMetaInfo = CardMeta::GetMetaByCardName("CroneWeavess");
    Power        = dynamic_cast<UnitMeta *>(CardMetaInfo)->GetInitialPower();
}


void CroneWeavess::OnDeploy()
{
    auto success = GlobalGameController->DeployCardFromContainerToBattleLine(
        "CroneBrewess", "AlliedDeck", SelectedLine, SelectedIndex + 1
    );

    GlobalGameController->DeployCardFromContainerToBattleLine(
        "CroneWhispess", "AlliedDeck", SelectedLine, SelectedIndex + (success ? 2 : 1)
    );
}
