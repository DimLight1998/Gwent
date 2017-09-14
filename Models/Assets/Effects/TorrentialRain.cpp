//
// Created on 2017/09/03 at 23:01.
//

#include <QtCore/QDateTime>
#include "TorrentialRain.hpp"


void TorrentialRain::OnDestroy()
{ GlobalGameController->MoveCardFromCardsSetToCardsSet(CardId, GetFactionString() + "Grave", 0); }


TorrentialRain::TorrentialRain(GameController *gameController)
    : Effect(gameController)
{
    CardMetaInfo = CardMeta::GetMetaByCardName("TorrentialRain");
}


void TorrentialRain::OnDeploy()
{
    Card::OnDeploy();

    GlobalGameController->SetWeatherToBattleLine(SelectedLine, BattleLine::WeatherEnum::Rain);
    TorrentialRain::ExecuteDamage(GlobalGameController, SelectedLine);
}


void TorrentialRain::ExecuteDamage(GameController *gameController, const QString& battleLineName)
{
    auto         battleLine = gameController->GetBattleField()->GetBattleLineByName(battleLineName);
    QVector<int> unitsId;
    for (auto    item:battleLine->GetUnits())
    {
        unitsId.append(item);
    }

    std::mt19937 g(static_cast<unsigned int>(QDateTime::currentMSecsSinceEpoch()));
    std::shuffle(unitsId.begin(), unitsId.end(), g);

    auto damageNumber = qMin(unitsId.size(), 2);

    for (int i = 0; i < damageNumber; i++)
    {
        dynamic_cast<Unit *>(gameController->GetCardManager()->GetCardById(unitsId[i]))->Damage(1);
    }
}


void TorrentialRain::OnRoundUpdateHandler()
{
    // update weathers
    for (const auto& battleLineName :QVector<QString>({"EnemyMelee", "EnemyRanged", "EnemySiege"}))
    {
        auto battleLine = GlobalGameController->GetBattleField()->GetBattleLineByName(battleLineName);
        if (battleLine->GetWeather() == BattleLine::WeatherEnum::Rain)
        {
            TorrentialRain::ExecuteDamage(GlobalGameController, battleLineName);
            GlobalGameController->GetInteracting()->SetCheckPoint();
            break;
        }
    }
}
