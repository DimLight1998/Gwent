//
// Created on 2017/09/06 at 01:20.
//

#include "UnseenElder.hpp"
#include "../../Meta/UnitMeta.hpp"


UnseenElder::UnseenElder(GameController *gameController)
    : Unit(gameController)
{
    CardMetaInfo = CardMeta::GetMetaByCardName("UnseenElder");
    Power        = dynamic_cast<UnitMeta *>(CardMetaInfo)->GetInitialPower();
}


void UnseenElder::OnDeploy()
{
    Card::OnDeploy();

    for (int i = 0; i < 3; i++)
    {
        bool isValid = false;

        do
        {
            //check there is units on the field
            auto count = 0;
            count += GlobalGameController->GetBattleField()->GetBattleLineByName("AlliedSiege")->GetUnits().size();
            count += GlobalGameController->GetBattleField()->GetBattleLineByName("AlliedRanged")->GetUnits().size();
            count += GlobalGameController->GetBattleField()->GetBattleLineByName("AlliedMelee")->GetUnits().size();

            if (count <= 1)
            {
                break;
            }

            auto id = GlobalGameController->GetInteracting()->GetSelectedCardFromBattleField();
            if (GlobalGameController->IsThisUnitAllied(id) && id != CardId)
            {
                isValid = true;
            }

            if (isValid)
            {
                auto powerUp = dynamic_cast<Unit *>(GlobalGameController->GetCardManager()->GetCardById(id))
                    ->GetPowerUpWhenSwallowed();
                GainPower(powerUp);
                GlobalGameController->HandleUnitSwallowed(id);
            }
        }
        while (!isValid);
    }
}


void UnseenElder::OnDestroy()
{
    GlobalGameController->MoveCardFromCardsSetToCardsSet(CardId, GetFactionString() + "Discard", 0);
}
