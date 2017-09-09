//
// Created on 2017/09/04 at 10:41.
//

#include "WildHuntRider.hpp"
#include "../../Meta/UnitMeta.hpp"


WildHuntRider::WildHuntRider(GameController *gameController)
    : Unit(gameController)
{
    CardMetaInfo = CardMeta::GetMetaByCardName("WildHuntRider");
    Power        = dynamic_cast<UnitMeta *>(CardMetaInfo)->GetInitialPower();
}


void WildHuntRider::OnDestroy()
{
    GlobalGameController->MoveCardFromCardsSetToCardsSet(CardId, GetFactionString() + "Grave", 0);
}
