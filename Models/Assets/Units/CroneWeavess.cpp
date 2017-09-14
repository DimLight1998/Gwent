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
    Card::OnDeploy();

    GlobalGameController->DeployUnitFromContainerToBattleLine(
        "CroneBrewess", "AlliedDeck", SelectedLine, SelectedIndex + 1
    );

    GlobalGameController->DeployUnitFromContainerToBattleLine(
        "CroneWhispess", "AlliedDeck", SelectedLine, SelectedIndex + 1
    );
}


void CroneWeavess::OnDestroy()
{
    GlobalGameController->MoveCardFromCardsSetToCardsSet(CardId, GetFactionString() + "Grave", 0);
}
