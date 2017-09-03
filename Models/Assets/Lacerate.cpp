//
// Created on 2017/09/03 at 23:29.
//

#include "Lacerate.hpp"


Lacerate::Lacerate()
{
    CardMetaInfo = CardMeta::GetMetaByCardName("Lacerate");
}


void Lacerate::OnDeploy()
{
    auto battleLine = GlobalGameController->GetBattleField()->GetBattleLineByName(SelectedLine);

    for (auto& i:battleLine->GetUnits())
    {
        auto card = GlobalGameController->GetCardManager()->GetCardById(i);
        dynamic_cast<Unit *>(card)->Damage(3);
    }
}
