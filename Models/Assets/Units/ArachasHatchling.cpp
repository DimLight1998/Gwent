//
// Created on 2017/09/04 at 22:37.
//

#include "ArachasHatchling.hpp"
#include "../../Meta/UnitMeta.hpp"


ArachasHatchling::ArachasHatchling()
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
