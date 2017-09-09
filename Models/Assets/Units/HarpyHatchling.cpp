//
// Created on 2017/09/04 at 15:11.
//

#include "HarpyHatchling.hpp"
#include "../../Meta/UnitMeta.hpp"


HarpyHatchling::HarpyHatchling(GameController *gameController)
    : Unit(gameController)
{
    CardMetaInfo = CardMeta::GetMetaByCardName("HarpyHatchling");
    Power        = dynamic_cast<UnitMeta *>(CardMetaInfo)->GetInitialPower();
}


void HarpyHatchling::OnDestroy()
{
    GlobalGameController->MoveCardFromCardsSetToCardsSet(CardId, GetFactionString() + "Discard", 0);
}
