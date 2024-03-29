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
    Card::OnDeploy();

    auto enemyLine = SelectedLine;
    if (SelectedLine.startsWith("Allied"))
    {
        enemyLine.replace(0, 6, "Enemy");
    }

    GlobalGameController->SetWeatherToBattleLine(enemyLine, BattleLine::WeatherEnum::Frost);

    int count = 0;
    for (const auto& item:QVector<QString>({"EnemySiege", "EnemyRanged", "EnemyMelee"}))
    {
        if (item != enemyLine)
        {
            count += GlobalGameController->GetBattleField()->GetBattleLineByName(item)->GetUnits().size();
        }
    }

    auto isValid = false;

    if (count <= 0)
    {
        return;
    }

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
        }
    }
    while (!isValid);
}


void Caranthir::OnDestroy()
{
    GlobalGameController->MoveCardFromCardsSetToCardsSet(CardId, GetFactionString() + "Grave", 0);
}
