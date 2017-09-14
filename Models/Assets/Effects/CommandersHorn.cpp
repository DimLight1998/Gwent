//
// Created on 2017/09/04 at 00:27.
//

#include "CommandersHorn.hpp"


void CommandersHorn::OnDestroy()
{ GlobalGameController->MoveCardFromCardsSetToCardsSet(CardId, GetFactionString() + "Grave", 0); }


CommandersHorn::CommandersHorn(GameController *gameController)
    : Effect(gameController)
{
    CardMetaInfo = CardMeta::GetMetaByCardName("CommandersHorn");
}


void CommandersHorn::OnDeploy()
{
    Card::OnDeploy();

    auto id             = SelectedUnit;
    auto battleLineName = GlobalGameController->GetBattleField()->GetBattleLineContainingCard(id);
    auto battleLine     = GlobalGameController->GetBattleField()->GetBattleLineByName(battleLineName);

    for (int i = 0; i < battleLine->GetUnits().size(); i++)
    {
        if (battleLine->GetUnits()[i] == id)
        {
            auto cardManager = GlobalGameController->GetCardManager();

            dynamic_cast<Unit *>(cardManager->GetCardById(id))->GainPower(4);

            if (i - 1 >= 0)
            {
                dynamic_cast<Unit *>(cardManager->GetCardById(battleLine->GetUnits()[i - 1]))->GainPower(4);
            }

            if (i - 2 >= 0)
            {
                dynamic_cast<Unit *>(cardManager->GetCardById(battleLine->GetUnits()[i - 2]))->GainPower(4);
            }

            if (i + 1 < battleLine->GetUnits().size())
            {
                dynamic_cast<Unit *>(cardManager->GetCardById(battleLine->GetUnits()[i + 1]))->GainPower(4);
            }

            if (i + 2 < battleLine->GetUnits().size())
            {
                dynamic_cast<Unit *>(cardManager->GetCardById(battleLine->GetUnits()[i + 2]))->GainPower(4);
            }
        }
    }
}
