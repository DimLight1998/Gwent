//
// Created on 2017/09/05 at 19:27.
//

#include "Frightener.hpp"
#include "../../Containers/CardContainer.hpp"
#include "../../Meta/UnitMeta.hpp"


Frightener::Frightener(GameController *gameController)
    : Unit(gameController)
{
    CardMetaInfo = CardMeta::GetMetaByCardName("Frightener");
    Power        = dynamic_cast<UnitMeta *>(CardMetaInfo)->GetInitialPower();
}


void Frightener::OnDeploy()
{
    auto enemyLine = SelectedLine;
    auto isValid   = false;

    do
    {
        auto cardId = GlobalGameController->GetInteracting()->GetSelectedCardFromBattleField();

        auto sourceLine     = GlobalGameController->GetBattleField()->GetBattleLineContainingCard(cardId);

        QString deployLine;
        int     deployIndex = 0;

        if (GlobalGameController->IsThisUnitEnemy(cardId))
        {
            if (GlobalGameController->GetBattleField()->GetBattleLineContainingCard(cardId) != enemyLine)
            {

                GlobalGameController->GetInteracting()->GetSelectedUnitDeployLocation(deployLine, deployIndex);

                if (deployLine == enemyLine)
                {
                    isValid = true;
                }
            }
        }

        if (isValid)
        {
            GlobalGameController->MoveCardFromBattleLineToBattleLine(cardId, sourceLine, deployLine, deployIndex);
        }
    }
    while (!isValid);

    auto topId = GlobalGameController->GetBattleField()->GetCardContainerByName("AlliedDeck")->GetCards()[0];
    GlobalGameController->MoveCardFromCardsSetToCardsSet(topId, "AlliedDeck", "AlliedHand", 0);
}
