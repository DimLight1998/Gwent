//
// Created on 2017/09/03 at 17:40.
//

#include "BitingFrost.hpp"


void BitingFrost::OnDeploy()
{
    SelectedLine->SetWeather(BattleLine::WeatherEnum::Frost);
}


void BitingFrost::OnDestroy()
{
}


void BitingFrost::OnDeathWish()
{
}


BitingFrost::BitingFrost()
{
    CardMetaInfo = CardMeta::GetMetaByCardName("BitingFrost");
}
