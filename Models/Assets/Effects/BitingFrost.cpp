//
// Created on 2017/09/03 at 17:40.
//

#include "BitingFrost.hpp"


void BitingFrost::OnDeploy()
{
    GlobalGameController->SetWeatherToBattleLine(SelectedLine, BattleLine::WeatherEnum::Frost);
}


BitingFrost::BitingFrost(GameController *gameController)
    : Effect(gameController)
{
    CardMetaInfo = CardMeta::GetMetaByCardName("BitingFrost");
}
