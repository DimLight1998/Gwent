//
// Created on 2017/09/03 at 21:52.
//

#include "ImpenetrableFog.hpp"


ImpenetrableFog::ImpenetrableFog()
{
    CardMetaInfo = CardMeta::GetMetaByCardName("ImpenetrableFog");
}


void ImpenetrableFog::OnDeploy()
{
    GlobalGameController->SetWeatherToBattleLine(SelectedLine, BattleLine::WeatherEnum::Fog);

    auto fogletDeployLine = SelectedLine;
    if (fogletDeployLine.startsWith("Enemy"))
    {
        fogletDeployLine.replace(0, 5, "Allied");
    }

    // todo Maybe the location should be selected by player? Place to rightmost place now.
    int index = GlobalGameController->GetBattleField()->GetBattleLineByName(fogletDeployLine)->GetUnits().size();

    auto success = GlobalGameController->DeployCardFromContainerToBattleLine(
        "Foglet", "AlliedDeck", fogletDeployLine, index);

    if (!success)
    {
        GlobalGameController->DeployCardFromContainerToBattleLine("Foglet", "AlliedGrave", fogletDeployLine, index);
    }
}