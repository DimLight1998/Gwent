//
// Created on 2017/09/04 at 22:37.
//

#include "ArachasHatchling.hpp"
#include "../../Meta/UnitMeta.hpp"


ArachasHatchling::ArachasHatchling(GameController *gameController)
    : Unit(gameController)
{
    CardMetaInfo = CardMeta::GetMetaByCardName("ArachasHatchling");
    Power        = dynamic_cast<UnitMeta *>(CardMetaInfo)->GetInitialPower();
}


void ArachasHatchling::OnDeploy()
{
    bool success = true;

    while (success)
    {
        auto size = GlobalGameController->GetBattleField()->GetBattleLineByName("AlliedRanged")->GetUnits().size();

        success = GlobalGameController->DeployCardFromContainerToBattleLine(
            "Arachas", "AlliedDeck", "AlliedRanged", size
        );
    }
}


void ArachasHatchling::OnDestroy()
{
    GlobalGameController->MoveCardFromCardsSetToCardsSet(CardId, GetFactionString() + "Discard", 0);
}
