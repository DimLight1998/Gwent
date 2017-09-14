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
    Card::OnDeploy();

    GlobalGameController->DeployUnitFromContainerToBattleLine(
        "CroneWeavess", "AlliedDeck", SelectedLine, SelectedIndex + 1
    );

    GlobalGameController->DeployUnitFromContainerToBattleLine(
        "CroneWhispess", "AlliedDeck", SelectedLine, SelectedIndex + 1
    );
}


void CroneBrewess::OnDestroy()
{
    GlobalGameController->MoveCardFromCardsSetToCardsSet(CardId, GetFactionString() + "Grave", 0);
}
