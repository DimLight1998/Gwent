//
// Created on 2017/09/03 at 17:27.
//

#ifndef GWENT_GAMECONTROLLER_HPP
#define GWENT_GAMECONTROLLER_HPP

#include "../Models/Containers/BattleField.hpp"
#include "../Models/Containers/BattleLine.hpp"
#include "../Models/Containers/CardManager.hpp"


class CardManager;


class BattleField;


class GameController
{
private:
    BattleField *_battleField;
    CardManager *_cardManager;

public:
    /// \brief this function can deploy a unit to a specific battle line,
    /// then trigger its OnDeploy function
    /// \param cardId id of the card
    /// \param battleLineName the battle line it will be deployed to, format: (Enemy|Allied)(Melee|Ranged|Siege)
    /// \param index the index of the battle line, starting from 0
    /// \note the function won't check if the card can be deployed, it just does what is told
    void DeployUnitToBattleLine(int cardId, const QString& battleLineName, int index);

    /// \brief set weather to a specific battle line
    /// \param battleLineName the battle line weather will be set at, format: (Enemy|Allied)(Melee|Ranged|Siege)
    /// \param weather the weather, can be None
    void SetWeatherToBattleLine(const QString& battleLineName, BattleLine::WeatherEnum weather);
};


#endif //GWENT_GAMECONTROLLER_HPP
