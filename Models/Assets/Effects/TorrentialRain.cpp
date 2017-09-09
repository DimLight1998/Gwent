//
// Created on 2017/09/03 at 23:01.
//

#include "TorrentialRain.hpp"


void TorrentialRain::OnDestroy()
{ GlobalGameController->MoveCardFromCardsSetToCardsSet(CardId, GetFactionString() + "Grave", 0); }


TorrentialRain::TorrentialRain(GameController *gameController)
    : Effect(gameController)
{
    CardMetaInfo = CardMeta::GetMetaByCardName("TorrentialRain");
}


void TorrentialRain::OnDeploy()
{
    GlobalGameController->SetWeatherToBattleLine(SelectedLine, BattleLine::WeatherEnum::Rain);
}
