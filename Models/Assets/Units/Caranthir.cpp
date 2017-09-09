//
// Created on 2017/09/05 at 16:15.
//

#include "Caranthir.hpp"
#include "../../Meta/UnitMeta.hpp"


Caranthir::Caranthir(GameController *gameController)
    : Unit(gameController)
{
    CardMetaInfo = CardMeta::GetMetaByCardName("Caranthir");
    Power        = dynamic_cast<UnitMeta *>(CardMetaInfo)->GetInitialPower();
}


void Caranthir::OnDeploy()
{
    GlobalGameController->HandleGoldCardDeploying();

    auto count = 0;
    count += GlobalGameController->GetBattleField()->GetBattleLineByName("EnemySiege")->GetUnits().size();
    count += GlobalGameController->GetBattleField()->GetBattleLineByName("EnemyRanged")->GetUnits().size();
    count += GlobalGameController->GetBattleField()->GetBattleLineByName("EnemyMelee")->GetUnits().size();

    if (count <= 0)
    {
        return;
    }

    auto enemyLine = SelectedLine;
    if (SelectedLine.startsWith("Allied"))
    {
        enemyLine.replace(0, 6, "Enemy");
    }

    auto isValid = false;

    do
    {
        auto cardId = GlobalGameController->GetInteracting()->GetSelectedCardFromBattleField();

        auto sourceLine = GlobalGameController->GetBattleField()->GetBattleLineContainingCard(cardId);

        QString deployLine;
        int     deployIndex;

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
            GlobalGameController->SetWeatherToBattleLine(deployLine, BattleLine::WeatherEnum::Frost);
        }
    }
    while (!isValid);
}


void Caranthir::OnDestroy()
{
    GlobalGameController->MoveCardFromCardsSetToCardsSet(CardId, GetFactionString() + "Grave", 0);
}
