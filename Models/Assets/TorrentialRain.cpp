//
// Created on 2017/09/03 at 23:01.
//

#include "TorrentialRain.hpp"


TorrentialRain::TorrentialRain()
{
    CardMetaInfo = CardMeta::GetMetaByCardName("TorrentialRain");
}


void TorrentialRain::OnDeploy()
{
    GlobalGameController->SetWeatherToBattleLine(SelectedLine, BattleLine::WeatherEnum::Rain);
}
