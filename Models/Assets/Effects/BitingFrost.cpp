//
// Created on 2017/09/03 at 17:40.
//

#include "BitingFrost.hpp"


void BitingFrost::OnDeploy()
{
    GlobalGameController->SetWeatherToBattleLine(SelectedLine, BattleLine::WeatherEnum::Frost);
}

BitingFrost::BitingFrost()
{
    CardMetaInfo = CardMeta::GetMetaByCardName("BitingFrost");
}
