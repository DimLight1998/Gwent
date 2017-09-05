//
// Created on 2017/09/05 at 23:33.
//

#include "VranWarrior.hpp"


VranWarrior::VranWarrior()
{
    CardMetaInfo = CardMeta::GetMetaByCardName("VranWarrior");
    CountDown    = 2;
}


void VranWarrior::OnDeploy()
{
    auto battleLineName  = GlobalGameController->GetBattleField()->GetBattleLineContainingCard(CardId);
    auto battleLineUnits = GlobalGameController->GetBattleField()->GetBattleLineByName(battleLineName)->GetUnits();
    auto size            = battleLineUnits.size();

    if (SelectedIndex < size - 1)
    {
        auto swallowedUnitId = battleLineUnits[SelectedIndex + 1];
        auto powerUp         = GlobalGameController->GetPowerUpOfSwallowing(swallowedUnitId);
        GainPower(powerUp);
        dynamic_cast<Unit *>(GlobalGameController->GetCardManager()->GetCardById(swallowedUnitId))->Destroy();
        GlobalGameController->HandleUnitSwallowed();
    }
}


void VranWarrior::RoundUpdate()
{
    CountDown--;
    if (CountDown == 0)
    {
        CountDown = 2;
        auto currentLine  = GlobalGameController->GetBattleField()->GetBattleLineContainingCard(CardId);
        auto units        = GlobalGameController->GetBattleField()->GetBattleLineByName(currentLine)->GetUnits();
        int  currentIndex = 0;

        for (int i = 0; i < units.size(); i++)
        {
            if (units[i] == CardId)
            {
                currentIndex = i;
                break;
            }
        }

        if (currentIndex < units.size() - 1)
        {
            auto swallowedUnitId = units[currentIndex + 1];
            auto powerUp         = GlobalGameController->GetPowerUpOfSwallowing(swallowedUnitId);
            GainPower(powerUp);
            dynamic_cast<Unit *>(GlobalGameController->GetCardManager()->GetCardById(swallowedUnitId))->Destroy();
            GlobalGameController->HandleUnitSwallowed();
        }
    }
}
// todo update roundly
