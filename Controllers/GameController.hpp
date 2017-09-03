//
// Created on 2017/09/03 at 17:27.
//

#ifndef GWENT_GAMECONTROLLER_HPP
#define GWENT_GAMECONTROLLER_HPP

#include "../Models/Containers/BattleField.hpp"
#include "../Models/Containers/BattleLine.hpp"
#include "../Models/Containers/CardManager.hpp"


class GameController
{
private:
    BattleField *_battleField;
    CardManager *_cardManager;

public:
    //! \brief this function can deploy a unit to a specific battle line,
    //! then trigger its OnDeploy function
    //! \param cardId id of the card
    //! \param battleLine the battle line it will be deployed to
    //! \param index the index of the battle line, starting from 0
    //! \note the function won't check if the card can be deployed, it just does what is told
    void DeployUnitToBattleLine(int cardId, BattleLine *battleLine, int index);
};


#endif //GWENT_GAMECONTROLLER_HPP
