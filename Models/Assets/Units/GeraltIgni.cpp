//
// Created on 2017/09/04 at 09:57.
//

#include "GeraltIgni.hpp"


GeraltIgni::GeraltIgni()
{
    CardMetaInfo = CardMeta::GetMetaByCardName("GeraltIgni");
}


void GeraltIgni::OnDeploy()
{
    auto enemyLine = SelectedLine;
    enemyLine.replace(0, 6, "Enemy");

    int       highestPower = 0;
    int       totalPower   = 0;
    for (auto i:GlobalGameController->GetBattleField()->GetBattleLineByName(enemyLine)->GetUnits())
    {
        auto unit = dynamic_cast<Unit *>(GlobalGameController->GetCardManager()->GetCardById(i));
        totalPower += unit->GetPower();
        if (unit->GetPower() > highestPower)
        {
            highestPower = unit->GetPower();
        }
    }

    if (totalPower >= 25)
    {
        for (auto i:GlobalGameController->GetBattleField()->GetBattleLineByName(enemyLine)->GetUnits())
        {
            auto unit = dynamic_cast<Unit *>(GlobalGameController->GetCardManager()->GetCardById(i));
            if (unit->GetPower() == highestPower)
            {
                unit->Destroy();
            }
        }
    }
}
