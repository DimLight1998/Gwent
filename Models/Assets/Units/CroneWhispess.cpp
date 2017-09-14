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
    Card::OnDeploy();

    GlobalGameController->DeployUnitFromContainerToBattleLine(
        "CroneBrewess", "AlliedDeck", SelectedLine, SelectedIndex + 1
    );

    GlobalGameController->DeployUnitFromContainerToBattleLine(
        "CroneWeavess", "AlliedDeck", SelectedLine, SelectedIndex + 1
    );
}


void CroneWhispess::OnDestroy()
{
    GlobalGameController->MoveCardFromCardsSetToCardsSet(CardId, GetFactionString() + "Grave", 0);
}
