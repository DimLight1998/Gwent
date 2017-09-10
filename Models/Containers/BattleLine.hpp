//
// Created on 2017/09/03 at 16:10.
//

#ifndef GWENT_BATTLELINE_HPP
#define GWENT_BATTLELINE_HPP

#include <QVector>

class BattleLine
{
public:
    enum class WeatherEnum
    {
        Rain, Frost, Fog, None
    };

protected:
    QVector<int> Units; ///< stores id of the units
    WeatherEnum  Weather;
public:
    BattleLine();
    WeatherEnum GetWeather() const;
    void SetWeather(WeatherEnum weather);

    /// \brief this function can insert a unit to the battle line
    /// \param unitId the id of the unit
    /// \param index the index of the inserting position, ranged from 0 to Units.size()
    /// \throw 0 if index not correct
    void InsertUnit(int unitId, int index);

    /// \brief test if the battle line contains the certain card
    /// \param id id of the card
    /// \return true if yes, otherwise no
    bool IsBattleLineContainingCard(int id);

    /// \brief remove the card of the id from the battle line
    /// \param id id of the card
    /// \throw 23975462 if id incorrect
    void RemoveCardOfId(int id);


    const QVector<int>& GetUnits() const;

    QString GetWeatherString() const;

    /// \brief convert the battle line to a string to synchronize with separator %
    /// \return a string which can represent the status of the battle line
    QString ToString();

    /// \brief build the battle line from a string
    /// \param source the string defining the battle line
    void UpdateFromString(const QString& source);
};


#endif //GWENT_BATTLELINE_HPP
