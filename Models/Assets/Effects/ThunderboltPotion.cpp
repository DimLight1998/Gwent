//
// Created on 2017/09/04 at 09:28.
//

#include "ThunderboltPotion.hpp"


ThunderboltPotion::ThunderboltPotion()
{
    CardMetaInfo = CardMeta::GetMetaByCardName("ThunderboltPotion");
}


void ThunderboltPotion::OnDeploy()
{
    auto id             = SelectedUnit;
    auto battleLineName = GlobalGameController->GetBattleField()->GetBattleLineContainingCard(id);
    auto battleLine     = GlobalGameController->GetBattleField()->GetBattleLineByName(battleLineName);

    for (int i = 0; i < battleLine->GetUnits().size(); i++)
    {
        if (battleLine->GetUnits()[i] == id)
        {
            auto cardManager = GlobalGameController->GetCardManager();

            auto unit = dynamic_cast<Unit *>(cardManager->GetCardById(id));
            unit->GainPower(3);
            unit->GainArmor(2);

            if (i - 1 >= 0)
            {
                auto unitLeft = dynamic_cast<Unit *>(cardManager->GetCardById(battleLine->GetUnits()[i - 1]));
                unitLeft->GainPower(3);
                unitLeft->GainArmor(2);
            }

            if (i + 1 <= battleLine->GetUnits().size())
            {
                auto unitRight = dynamic_cast<Unit *>(cardManager->GetCardById(battleLine->GetUnits()[i + 1]));
                unitRight->GainPower(3);
                unitRight->GainArmor(2);
            }
        }
    }
}
