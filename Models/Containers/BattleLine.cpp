//
// Created on 2017/09/03 at 16:10.
//

#include "BattleLine.hpp"


BattleLine::WeatherEnum BattleLine::GetWeather() const
{
    return Weather;
}


void BattleLine::SetWeather(BattleLine::WeatherEnum Weather)
{
    BattleLine::Weather = Weather;
}
