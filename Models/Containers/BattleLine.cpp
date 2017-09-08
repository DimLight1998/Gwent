//
// Created on 2017/09/03 at 16:10.
//

#include "BattleLine.hpp"


BattleLine::WeatherEnum BattleLine::GetWeather() const
{
    return Weather;
}


void BattleLine::SetWeather(BattleLine::WeatherEnum weather)
{
    BattleLine::Weather = weather;
}


void BattleLine::InsertUnit(int unitId, int index)
{
    if (index < 0 || index > Units.size())
    {
        throw 0;
    }

    Units.insert(unitId, index);
}


const QVector<int>& BattleLine::GetUnits() const
{
    return Units;
}


bool BattleLine::IsBattleLineContainingCard(int id)
{
    for (auto& i:Units)
    {
        if (i == id)
        {
            return true;
        }
    }

    return false;
}


void BattleLine::RemoveCardOfId(int id)
{
    try
    {
        for (int i = 0; i < Units.size(); i++)
        {
            if (Units[i] == id)
            {
                Units.remove(i);
                return;
            }
        }
    }
    catch (...)
    {
        throw 23975462;
    }
}


BattleLine::BattleLine()
{
    Units   = QVector<int>();
    Weather = WeatherEnum::None;
}
