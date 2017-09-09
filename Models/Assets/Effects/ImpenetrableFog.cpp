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

    GlobalGameController->HandleImpenetrableFogDeployed(SelectedLine);
}