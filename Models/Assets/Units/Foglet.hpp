//
// Created on 2017/09/03 at 21:55.
//

#ifndef GWENT_FOGLET_HPP
#define GWENT_FOGLET_HPP

#include "../../Card/Unit.hpp"


class Foglet : public Unit
{
public:
    Foglet(GameController *gameController);
    void OnDestroy() override;
    void
    OnWeatherChangedHandler(
        const QString& battleLineName,
        BattleLine::WeatherEnum originalWeather,
        BattleLine::WeatherEnum newWeather
    ) override;
};


#endif //GWENT_FOGLET_HPP
