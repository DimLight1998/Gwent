//
// Created on 2017/09/05 at 15:36.
//

#include "Dagon.hpp"
#include "../../Card/Effect.hpp"
#include "../../Meta/UnitMeta.hpp"


Dagon::Dagon(GameController *gameController)
    : Unit(gameController)
{
    CardMetaInfo = CardMeta::GetMetaByCardName("Dagon");
    Power        = dynamic_cast<UnitMeta *>(CardMetaInfo)->GetInitialPower();
}


void Dagon::OnDeploy()
{
    Card::OnDeploy();

    QVector<CardMeta *> cardMeta = QVector<CardMeta *>(
        {
            CardMeta::GetMetaByCardName("BitingFrost"),
            CardMeta::GetMetaByCardName("TorrentialRain"),
            CardMeta::GetMetaByCardName("ImpenetrableFog")
        });

    auto selectedCardMeta = GlobalGameController->GetInteracting()->GetSelectedCardFromSpanningCards(cardMeta);

    for (auto i:cardMeta)
    {
        delete i;
    }

    auto id = GlobalGameController->SpawnCard(selectedCardMeta.GetName(), "AlliedDiscard", 0);

    GlobalGameController->DeployTheCardOfId(id);
}


void Dagon::OnDestroy()
{
    GlobalGameController->MoveCardFromCardsSetToCardsSet(CardId, GetFactionString() + "Discard", 0);
}
