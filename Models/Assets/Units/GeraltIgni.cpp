//
// Created on 2017/09/04 at 09:57.
//

#include "GeraltIgni.hpp"
#include "../../Meta/UnitMeta.hpp"


GeraltIgni::GeraltIgni(GameController *gameController)
    : Unit(gameController)
{
    CardMetaInfo = CardMeta::GetMetaByCardName("GeraltIgni");
    Power        = dynamic_cast<UnitMeta *>(CardMetaInfo)->GetInitialPower();
}


void GeraltIgni::OnDeploy()
{
    Card::OnDeploy();

    auto enemyLine = SelectedLine;
    enemyLine.replace(0, 6, "Enemy");

    int       highestPower = 0;
    int       totalPower   = 0;
    for (auto i:GlobalGameController->GetBattleField()->GetBattleLineByName(enemyLine)->GetUnits())
    {
        auto unit = dynamic_cast<Unit *>(GlobalGameController->GetCardManager()->GetCardById(i));
        totalPower += unit->GetPower();
        if (unit->GetPower() > highestPower)
        {
            highestPower = unit->GetPower();
        }
    }

    if (totalPower >= 25)
    {
        QVector<Unit *> destoryList;
        for (auto       i:GlobalGameController->GetBattleField()->GetBattleLineByName(enemyLine)->GetUnits())
        {
            auto unit = dynamic_cast<Unit *>(GlobalGameController->GetCardManager()->GetCardById(i));
            if (unit->GetPower() == highestPower)
            {
                destoryList.append(unit);
            }
        }

        for (const auto item:destoryList)
        {
            item->Destroy();
        }
    }
}


void GeraltIgni::OnDestroy()
{
    GlobalGameController->MoveCardFromCardsSetToCardsSet(CardId, GetFactionString() + "Grave", 0);
}
