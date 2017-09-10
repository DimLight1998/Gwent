//
// Created on 2017/09/03 at 16:10.
//

#include "BattleLine.hpp"
#include <QDebug>


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

    Units.insert(index, unitId);
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


QString BattleLine::GetWeatherString() const
{
    switch (Weather)
    {
    case WeatherEnum::Rain:return "Rain";
    case WeatherEnum::Frost:return "Frost";
    case WeatherEnum::Fog:return "Fog";
    case WeatherEnum::None:return "None";
    }
}


QString BattleLine::ToString()
{
    auto weather = QString();
    switch (Weather)
    {
    case WeatherEnum::Rain:
    {
        weather = "Rain";
        break;
    }
    case WeatherEnum::Frost:
    {
        weather = "Frost";
        break;
    }
    case WeatherEnum::Fog:
    {
        weather = "Fog";
        break;
    }
    case WeatherEnum::None:
    {
        weather = "None";
        break;
    }
    }

    auto list = QStringList();

    for (const auto item:Units)
    {
        list.append(QString::number(item));
    }

    return weather + (list.empty() ? "" : "%") + list.join('%');
}


void BattleLine::UpdateFromString(const QString& source)
{
    auto list = source.split('%', QString::SkipEmptyParts);

    auto weather = list[0];

    if (weather == "Rain")
    { Weather = WeatherEnum::Rain; }
    if (weather == "Frost")
    { Weather = WeatherEnum::Frost; }
    if (weather == "Fog")
    { Weather = WeatherEnum::Fog; }
    if (weather == "None")
    { Weather = WeatherEnum::None; }

    Units.clear();

    if (list.size() > 1)
    {
        for (const auto& item:list.mid(1, -1))
        {
            Units.append(item.toInt());
        }
    }
}
