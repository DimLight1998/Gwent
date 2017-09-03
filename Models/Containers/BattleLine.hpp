//
// Created on 2017/09/03 at 16:10.
//

#ifndef GWENT_BATTLELINE_HPP
#define GWENT_BATTLELINE_HPP

#include <QVector>
#include "../Card/Unit.hpp"


class BattleLine
{
public:
    enum class WeatherEnum
    {
        Rain, Frost, Fog, None
    };

protected:
    QVector<Unit *> Units;
    WeatherEnum     Weather;
public:
    WeatherEnum GetWeather() const;
    void SetWeather(WeatherEnum Weather);
};


#endif //GWENT_BATTLELINE_HPP
