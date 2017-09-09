//
// Created on 2017/09/05 at 11:04.
//

#include "ClearSkies.hpp"


void ClearSkies::OnDestroy()
{ GlobalGameController->MoveCardFromCardsSetToCardsSet(CardId, GetFactionString() + "Grave", 0); }


ClearSkies::ClearSkies(GameController *gameController)
    : Effect(gameController)
{
    CardMetaInfo = CardMeta::GetMetaByCardName("ClearSkies");
}


void ClearSkies::OnDeploy()
{
    for (auto& postfix:QVector<QString>({QString("Siege"), QString("Ranged"), QString("Melee")}))
    {
        GlobalGameController->SetWeatherToBattleLine("Allied" + postfix, BattleLine::WeatherEnum::None);
    }
}
