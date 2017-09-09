//
// Created on 2017/09/05 at 09:35.
//

#include "EarthElemental.hpp"
#include "../../Meta/UnitMeta.hpp"


EarthElemental::EarthElemental(GameController *gameController)
    : Unit(gameController)
{
    CardMetaInfo = CardMeta::GetMetaByCardName("EarthElemental");
    Power        = dynamic_cast<UnitMeta *>(CardMetaInfo)->GetInitialPower();
}


void EarthElemental::OnDeploy()
{
    SetHasShield(true);
}


void EarthElemental::OnDeathWish()
{
    auto battleLineName = GlobalGameController->GetBattleField()->GetBattleLineContainingCard(CardId);
    auto battleLine     = GlobalGameController->GetBattleField()->GetBattleLineByName(battleLineName);

    for (int i = 0; i < 2; i++)
    {
        auto size = battleLine->GetUnits().size();
        GlobalGameController->SpawnCard("LesserEarthElemental", SelectedLine, size);
    }
}


void EarthElemental::OnDestroy()
{
    OnDeathWish();
    GlobalGameController->MoveCardFromCardsSetToCardsSet(CardId, GetFactionString() + "Grave", 0);
}
