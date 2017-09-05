//
// Created on 2017/09/03 at 17:04.
//

#include "FirstLight.hpp"


void FirstLight::OnDeploy()
{
    QVector<CardMeta *> cardMeta = QVector<CardMeta *>(
        {
            CardMeta::GetMetaByCardName("ClearSkies"),
            CardMeta::GetMetaByCardName("Rally")
        });

    auto selectedCardMeta = GlobalGameController->GetInteracting()->GetSelectedCardFromSpanningCards(cardMeta);

    for (auto i:cardMeta)
    {
        delete i;
    }

    auto id = GlobalGameController->SpawnCard(selectedCardMeta.GetName(), "AlliedDiscard", 0);
    GlobalGameController->GetCardManager()->GetCardById(id)->OnDeploy();
}


FirstLight::FirstLight()
{
    CardMetaInfo = CardMeta::GetMetaByCardName("FirstLight");
}
