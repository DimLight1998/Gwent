//
// Created on 2017/09/05 at 23:33.
//

#include "VranWarrior.hpp"
#include "../../Meta/UnitMeta.hpp"


VranWarrior::VranWarrior(GameController *gameController)
    : Unit(gameController)
{
    CardMetaInfo = CardMeta::GetMetaByCardName("VranWarrior");
    CountDown    = 2;
    Power        = dynamic_cast<UnitMeta *>(CardMetaInfo)->GetInitialPower();
}


void VranWarrior::OnDeploy()
{
    Card::OnDeploy();

    auto battleLineName  = GlobalGameController->GetBattleField()->GetBattleLineContainingCard(CardId);
    auto battleLineUnits = GlobalGameController->GetBattleField()->GetBattleLineByName(battleLineName)->GetUnits();
    auto size            = battleLineUnits.size();

    if (SelectedIndex < size - 1)
    {
        auto swallowedUnitId = battleLineUnits[SelectedIndex + 1];
        auto powerUp         = dynamic_cast<Unit *>(GlobalGameController->GetCardManager()
            ->GetCardById(swallowedUnitId))->GetPowerUpWhenSwallowed();
        GainPower(powerUp);
        GlobalGameController->HandleUnitSwallowed(swallowedUnitId);
    }

    CountDown = 2;
}


void VranWarrior::RoundUpdate()
{
    qDebug() << "Vran cd:" << GetTimeCount();
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
            auto powerUp         = dynamic_cast<Unit *>(GlobalGameController->GetCardManager()
                ->GetCardById(swallowedUnitId))->GetPowerUpWhenSwallowed();
            GainPower(powerUp);
            GlobalGameController->HandleUnitSwallowed(swallowedUnitId);
        }
    }
}


void VranWarrior::OnDestroy()
{
    GlobalGameController->MoveCardFromCardsSetToCardsSet(CardId, GetFactionString() + "Grave", 0);
}
// todo update roundly
