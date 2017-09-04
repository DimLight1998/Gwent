//
// Created on 2017/09/04 at 10:56.
//

#include "CroneBrewess.hpp"


CroneBrewess::CroneBrewess()
{
    CardMetaInfo = CardMeta::GetMetaByCardName("CroneBrewess");
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
