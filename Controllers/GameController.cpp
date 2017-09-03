//
// Created on 2017/09/03 at 17:27.
//

#include "GameController.hpp"

#include "../Models/Containers/CardContainer.hpp"


void GameController::DeployUnitToBattleLine(int cardId, const QString& battleLineName, int index)
{
    _battleField->GetBattleLineByName(battleLineName)->InsertUnit(cardId, index);
    _cardManager->GetCardById(cardId)->OnDeploy();
}


void GameController::SetWeatherToBattleLine(const QString& battleLineName, BattleLine::WeatherEnum weather)
{
    _battleField->GetBattleLineByName(battleLineName)->SetWeather(weather);
}


bool GameController::DeployCardFromContainerToBattleLine
    (const QString& cardName, const QString& containerName, const QString& battleLineName, int index)
{
    auto container = _battleField->GetCardContainerByName(containerName);

    for (auto& j:container->GetCards())
    {
        if (_cardManager->GetCardById(j)->GetCardMetaInfo()->GetName() == cardName)
        {
            container->RemoveCardOfId(j);
            DeployUnitToBattleLine(j, battleLineName, index);
            return true;
        }
    }

    return false;
}


BattleField *GameController::GetBattleField() const
{
    return _battleField;
}


CardManager *GameController::GetCardManager() const
{
    return _cardManager;
}
