//
// Created on 2017/09/05 at 09:35.
//

#include "EarthElemental.hpp"


EarthElemental::EarthElemental()
{
    CardMetaInfo = CardMeta::GetMetaByCardName("EarthElemental");
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
        GlobalGameController->SpanCard("LesserEarthElemental", SelectedLine, size);
    }
}
