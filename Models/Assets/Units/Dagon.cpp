//
// Created on 2017/09/05 at 15:36.
//

#include "Dagon.hpp"
#include "../../Card/Effect.hpp"


Dagon::Dagon()
{
    CardMetaInfo = CardMeta::GetMetaByCardName("Dagon");
}


void Dagon::OnDeploy()
{
    QVector<CardMeta *> cardMeta = QVector<CardMeta *>(
        {
            CardMeta::GetMetaByCardName("BitingFrost"),
            CardMeta::GetMetaByCardName("FirstLight"),
            CardMeta::GetMetaByCardName("ImpenetrableFog")
        });

    auto selectedCardMeta = GlobalGameController->GetInteracting()->GetSelectedCardFromSpanningCards(cardMeta);

    for (auto i:cardMeta)
    {
        delete i;
    }

    auto id = GlobalGameController->SpawnCard(selectedCardMeta.GetName(), "AlliedDiscard", 0);

    auto isValid = false;
    do
    {
        auto battleLine = GlobalGameController->GetInteracting()->GetSelectedEffectDeployBattleLine();

        if (battleLine.startsWith("Enemy"))
        {
            isValid = true;
        }

        if (isValid)
        {
            dynamic_cast<Effect *>(GlobalGameController->GetCardManager()->GetCardById(id))
                ->SetSelectedLine(battleLine);

            GlobalGameController->GetCardManager()->GetCardById(id)->OnDeploy();
        }
    }
    while (!isValid);
}
