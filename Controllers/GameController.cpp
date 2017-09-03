//
// Created on 2017/09/03 at 17:27.
//

#include "GameController.hpp"


void GameController::DeployUnitToBattleLine(int cardId, const QString& battleLineName, int index)
{
    _battleField->GetBattleLineByName(battleLineName)->InsertUnit(cardId, index);
    _cardManager->GetCardById(cardId)->OnDeploy();
}
