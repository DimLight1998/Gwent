//
// Created on 2017/09/03 at 17:40.
//

#include "BitingFrost.hpp"


void BitingFrost::OnDeploy()
{
    GlobalGameController->SetWeatherToBattleLine(SelectedLine, BattleLine::WeatherEnum::Frost);
    BitingFrost::ExecuteDamage(GlobalGameController, SelectedLine);
}


void BitingFrost::OnDestroy()
{ GlobalGameController->MoveCardFromCardsSetToCardsSet(CardId, GetFactionString() + "Grave", 0); }


BitingFrost::BitingFrost(GameController *gameController)
    : Effect(gameController)
{
    CardMetaInfo = CardMeta::GetMetaByCardName("BitingFrost");
}


void BitingFrost::ExecuteDamage(GameController *gameController, const QString& battleLineName)
{
    auto battleLine = gameController->GetBattleField()->GetBattleLineByName(battleLineName);

    if (!battleLine->GetUnits().empty())
    {
        int lowestPower = INT_MAX;

        for (const auto item:battleLine->GetUnits())
        {
            if (lowestPower > dynamic_cast<Unit *>(gameController->GetCardManager()->GetCardById(item))->GetPower())
            {
                lowestPower = dynamic_cast<Unit *>(gameController->GetCardManager()->GetCardById(item))->GetPower();
            }
        }

        QVector<int>    lowestPowerUnitsId;
        for (const auto item:battleLine->GetUnits())
        {
            if (dynamic_cast<Unit *>(gameController->GetCardManager()->GetCardById(item))->GetPower() == lowestPower)
            {
                lowestPowerUnitsId.append(item);
            }
        }

        auto unitIndex = qrand() % (lowestPowerUnitsId.size());
        dynamic_cast<Unit *>(gameController->GetCardManager()->GetCardById(lowestPowerUnitsId[unitIndex]))->Damage(2);
    }
}
