//
// Created on 2017/09/04 at 22:36.
//

#include "LesserEarthElemental.hpp"
#include "../../Meta/UnitMeta.hpp"


LesserEarthElemental::LesserEarthElemental(GameController *gameController)
    : Unit(gameController)
{
    CardMetaInfo = CardMeta::GetMetaByCardName("LesserEarthElemental");
    Power        = dynamic_cast<UnitMeta *>(CardMetaInfo)->GetInitialPower();
}


void LesserEarthElemental::OnDestroy()
{
    GlobalGameController->MoveCardFromCardsSetToCardsSet(CardId, GetFactionString() + "Discard", 0);
}
