//
// Created on 2017/09/04 at 09:00.
//

#include <QtCore/QDateTime>
#include "BekkersTwistedMirror.hpp"


void BekkersTwistedMirror::OnDestroy()
{ GlobalGameController->MoveCardFromCardsSetToCardsSet(CardId, GetFactionString() + "Grave", 0); }


BekkersTwistedMirror::BekkersTwistedMirror(GameController *gameController)
    : Effect(gameController)
{
    CardMetaInfo = CardMeta::GetMetaByCardName("BekkersTwistedMirror");
}


void BekkersTwistedMirror::OnDeploy()
{
    Card::OnDeploy();
    // search for at least one unit
    bool hasAtLeastOneUnitOnField = false;
    int  initialId                = 0;

    for (const auto& prefix:QVector<QString>({QString("Enemy"), QString("Allied")}))
    {
        for (const auto& postfix:QVector<QString>({QString("Siege"), QString("Ranged"), QString("Melee")}))
        {
            if (!GlobalGameController->GetBattleField()->GetBattleLineByName(prefix + postfix)->GetUnits().empty())
            {
                hasAtLeastOneUnitOnField = true;
                initialId =
                    GlobalGameController->GetBattleField()->GetBattleLineByName(prefix + postfix)->GetUnits()[0];
            }
        }
    }

    // no units is on the field!
    if (!hasAtLeastOneUnitOnField)
    {
        return;
    }

    QVector<int> highestUnitIds;
    QVector<int> lowestUnitIds;

    highestUnitIds.append(initialId);
    lowestUnitIds.append(initialId);

    for (const auto& prefix:QVector<QString>({QString("Enemy"), QString("Allied")}))
    {
        for (const auto& postfix:QVector<QString>({QString("Siege"), QString("Ranged"), QString("Melee")}))
        {
            auto units = GlobalGameController->GetBattleField()->GetBattleLineByName(prefix + postfix)->GetUnits();
            for (auto& unit :units)
            {
                auto thisUnit = dynamic_cast<Unit *>(GlobalGameController->GetCardManager()->GetCardById(unit));

                auto highestUnit = dynamic_cast<Unit *>(GlobalGameController->GetCardManager()
                    ->GetCardById(highestUnitIds[0]));

                auto lowestUnit = dynamic_cast<Unit *>(GlobalGameController->GetCardManager()
                    ->GetCardById(lowestUnitIds[0]));

                if (thisUnit->GetPower() == highestUnit->GetPower())
                {
                    highestUnitIds.append(unit);
                }

                if (thisUnit->GetPower() == lowestUnit->GetPower())
                {
                    lowestUnitIds.append(unit);
                }

                if (thisUnit->GetPower() > highestUnit->GetPower())
                {
                    highestUnitIds.clear();
                    highestUnitIds.append(unit);
                }
                if (thisUnit->GetPower() < lowestUnit->GetPower())
                {
                    lowestUnitIds.clear();
                    lowestUnitIds.append(unit);
                }
            }
        }
    }

    qsrand(static_cast<uint>(QDateTime::currentMSecsSinceEpoch()));

    auto highestUnitId = highestUnitIds[qrand() % highestUnitIds.size()];
    auto lowestUnitId  = lowestUnitIds[qrand() % lowestUnitIds.size()];

    auto highestUnit = dynamic_cast<Unit *>(GlobalGameController->GetCardManager()->GetCardById(highestUnitId));
    auto lowestUnit  = dynamic_cast<Unit *>(GlobalGameController->GetCardManager()->GetCardById(lowestUnitId));

    int damage = highestUnit->GetPower();
    if (damage > 10)
    {
        damage = 10;
    }

    highestUnit->
        DamageIgnoringArmorAndShield(damage);
    lowestUnit->
        GainPower(damage);
}
