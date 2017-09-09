//
// Created on 2017/09/05 at 09:22.
//

#include "WoodlandSpirit.hpp"
#include "../../Meta/UnitMeta.hpp"


WoodlandSpirit::WoodlandSpirit(GameController *gameController)
    : Unit(gameController)
{
    CardMetaInfo = CardMeta::GetMetaByCardName("WoodlandSpirit");
    Power        = dynamic_cast<UnitMeta *>(CardMetaInfo)->GetInitialPower();
}


void WoodlandSpirit::OnDeploy()
{
    GlobalGameController->HandleGoldCardDeploying();

    auto selectedLine     = SelectedLine;
    auto alliedBattleLine = GlobalGameController->GetBattleField()->GetBattleLineByName(selectedLine);

    auto enemyLine = selectedLine;

    if (enemyLine.startsWith("Allied"))
    {
        enemyLine.replace(0, 6, "Enemy");
    }

    for (int i = 0; i < 3; i++)
    {
        auto size = alliedBattleLine->GetUnits().size();
        GlobalGameController->SpawnCard("RabidWolf", selectedLine, size);
    }

    GlobalGameController->SetWeatherToBattleLine(enemyLine, BattleLine::WeatherEnum::Frost);
}


void WoodlandSpirit::OnDestroy()
{
    GlobalGameController->MoveCardFromCardsSetToCardsSet(CardId, GetFactionString() + "Grave", 0);
}
