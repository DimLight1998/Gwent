//
// Created on 2017/09/03 at 21:55.
//

#include "Foglet.hpp"
#include "../../Meta/UnitMeta.hpp"


Foglet::Foglet(GameController *gameController)
    : Unit(gameController)
{
    CardMetaInfo = CardMeta::GetMetaByCardName("Foglet");
    Power        = dynamic_cast<UnitMeta *>(CardMetaInfo)->GetInitialPower();
}


void Foglet::OnDestroy()
{
    Card::OnDeploy();

    GlobalGameController->MoveCardFromCardsSetToCardsSet(CardId, GetFactionString() + "Grave", 0);
}


void Foglet::OnWeatherChangedHandler(
    const QString& battleLineName, BattleLine::WeatherEnum originalWeather, BattleLine::WeatherEnum newWeather
)
{
    if (originalWeather != BattleLine::WeatherEnum::Fog && newWeather == BattleLine::WeatherEnum::Fog)
    {
        if (battleLineName.startsWith("Enemy"))
        {
            auto deployBattleLineName = battleLineName;
            deployBattleLineName.replace(0, 5, "Allied");

            int index = GlobalGameController->GetBattleField()->GetBattleLineByName(deployBattleLineName)->GetUnits()
                .size();

            auto success = GlobalGameController
                ->DeployUnitFromContainerToBattleLine("Foglet", "AlliedDeck", deployBattleLineName, index);

            if (!success)
            {
                GlobalGameController
                    ->DeployUnitFromContainerToBattleLine("Foglet", "AlliedGrave", deployBattleLineName, index);
                GlobalGameController->Interacting->SetCheckPoint();
            }
        }
    }
    else if (originalWeather == BattleLine::WeatherEnum::Frost)
    {
        for (const auto& prefix:QVector<QString>({"Allied", "Enemy"}))
        {
            for (const auto& postfix:QVector<QString>({"Melee", "Siege", "Ranged"}))
            {
                auto weather = GlobalGameController->GetBattleField()->GetBattleLineByName(prefix + postfix)
                    ->GetWeather();
                if (weather == BattleLine::WeatherEnum::Frost)
                {
                    return;
                }
            }
        }

        QVector<int> destroyList;

        for (const auto& prefix:QVector<QString>({"Allied", "Enemy"}))
        {
            for (const auto& postfix:QVector<QString>({"Melee", "Siege", "Ranged"}))
            {
                auto            battleLine = GlobalGameController->GetBattleField()
                    ->GetBattleLineByName(prefix + postfix);
                for (const auto item:battleLine->GetUnits())
                {
                    if (GlobalGameController->GetCardManager()->GetCardById(item)->GetCardMetaInfo()->GetName()
                        == "Foglet")
                    {
                        destroyList.append(item);
                    }
                }
            }
        }

        for (const auto item:destroyList)
        {
            dynamic_cast<Unit *>(GlobalGameController->GetCardManager()->GetCardById(item))->Destroy();
        }
    }
}
