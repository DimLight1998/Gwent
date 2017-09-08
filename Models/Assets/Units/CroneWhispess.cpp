//
// Created on 2017/09/04 at 10:59.
//

#include "CroneWhispess.hpp"
#include "../../Meta/UnitMeta.hpp"


CroneWhispess::CroneWhispess()
{
    CardMetaInfo = CardMeta::GetMetaByCardName("CroneWhispess");
    Power        = dynamic_cast<UnitMeta *>(CardMetaInfo)->GetInitialPower();
}


void CroneWhispess::OnDeploy()
{
    GlobalGameController->DeployCardFromContainerToBattleLine(
        "CroneBrewess", "AlliedDeck", SelectedLine, SelectedIndex + 1
    );

    GlobalGameController->DeployCardFromContainerToBattleLine(
        "CroneWeavess", "AlliedDeck", SelectedLine, SelectedIndex + 2
    );
}
