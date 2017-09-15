//
// Created on 2017/09/03 at 23:29.
//

#include "Lacerate.hpp"


void Lacerate::OnDestroy()
{ GlobalGameController->MoveCardFromCardsSetToCardsSet(CardId, GetFactionString() + "Grave", 0); }


Lacerate::Lacerate(GameController *gameController)
    : Effect(gameController)
{
    CardMetaInfo = CardMeta::GetMetaByCardName("Lacerate");
}


void Lacerate::OnDeploy()
{
    Card::OnDeploy();

    auto battleLine = GlobalGameController->GetBattleField()->GetBattleLineByName(SelectedLine);

    auto damageList = QVector<Unit *>();

    for (auto& i:battleLine->GetUnits())
    {
        damageList.append(dynamic_cast<Unit *>(GlobalGameController->GetCardManager()->GetCardById(i)));
    }

    for (auto item:damageList)
    {
        item->Damage(3);
    }
}
