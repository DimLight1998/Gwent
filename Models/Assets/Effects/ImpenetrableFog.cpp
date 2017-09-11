//
// Created on 2017/09/03 at 21:52.
//

#include "ImpenetrableFog.hpp"


void ImpenetrableFog::OnDestroy()
{ GlobalGameController->MoveCardFromCardsSetToCardsSet(CardId, GetFactionString() + "Grave", 0); }


ImpenetrableFog::ImpenetrableFog(GameController *gameController)
    : Effect(gameController)
{
    CardMetaInfo = CardMeta::GetMetaByCardName("ImpenetrableFog");
}


void ImpenetrableFog::OnDeploy()
{
    GlobalGameController->SetWeatherToBattleLine(SelectedLine, BattleLine::WeatherEnum::Fog);
    ImpenetrableFog::ExecuteDamage(GlobalGameController, SelectedLine);
    GlobalGameController->HandleImpenetrableFogDeployed(SelectedLine);
}


void ImpenetrableFog::ExecuteDamage(GameController *gameController, const QString& battleLineName)
{
    auto battleLine = gameController->GetBattleField()->GetBattleLineByName(battleLineName);

    if (!battleLine->GetUnits().empty())
    {
        int highestPower = INT_MIN;

        for (const auto item:battleLine->GetUnits())
        {
            if (highestPower < dynamic_cast<Unit *>(gameController->GetCardManager()->GetCardById(item))->GetPower())
            {
                highestPower = dynamic_cast<Unit *>(gameController->GetCardManager()->GetCardById(item))->GetPower();
            }
        }

        QVector<int>    highestPowerUnitsId;
        for (const auto item:battleLine->GetUnits())
        {
            if (dynamic_cast<Unit *>(gameController->GetCardManager()->GetCardById(item))->GetPower() == highestPower)
            {
                highestPowerUnitsId.append(item);
            }
        }

        auto unitIndex = qrand() % (highestPowerUnitsId.size());
        dynamic_cast<Unit *>(gameController->GetCardManager()->GetCardById(highestPowerUnitsId[unitIndex]))->Damage(2);
    }
}
