//
// Created on 2017/09/05 at 11:04.
//

#include "ClearSkies.hpp"


ClearSkies::ClearSkies()
{
    CardMetaInfo = CardMeta::GetMetaByCardName("ClearSkies");
}


void ClearSkies::OnDeploy()
{
    for (auto& postfix:QVector<QString>({QString("Siege"), QString("Ranged"), QString("Melee")}))
    {
        GlobalGameController->SetWeatherToBattleLine("Allied" + postfix, BattleLine::WeatherEnum::None);
    }
}
