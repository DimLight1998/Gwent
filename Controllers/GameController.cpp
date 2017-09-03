//
// Created on 2017/09/03 at 17:27.
//

#include "GameController.hpp"


void GameController::DeployUnitToBattleLine(int cardId, BattleLine *battleLine, int index)
{
    battleLine->InsertUnit(cardId, index);
    _cardManager->GetCardById(cardId)->OnDeploy();
}
