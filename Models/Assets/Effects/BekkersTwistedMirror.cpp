//
// Created on 2017/09/04 at 09:00.
//

#include "BekkersTwistedMirror.hpp"


BekkersTwistedMirror::BekkersTwistedMirror()
{
    CardMetaInfo = CardMeta::GetMetaByCardName("BekkersTwistedMirror");
}


void BekkersTwistedMirror::OnDeploy()
{
    // search for at least one unit
    bool hasAtLeastOneUnitOnField = false;
    int  initialId                = 0;

    for (const auto& prefix:QVector({QString("Enemy"), QString("Allied")}))
    {
        for (const auto& postfix:QVector({QString("Siege"), QString("Ranged"), QString("Melee")}))
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

    int highestUnitId = initialId;
    int LowestUnitId  = initialId;

    for (const auto& prefix:QVector({QString("Enemy"), QString("Allied")}))
    {
        for (const auto& postfix:QVector({QString("Siege"), QString("Ranged"), QString("Melee")}))
        {
            auto units = GlobalGameController->GetBattleField()->GetBattleLineByName(prefix + postfix)->GetUnits();
            for (auto& unit :units)
            {
                auto thisUnit    = dynamic_cast<Unit *>(GlobalGameController->GetCardManager()->GetCardById(unit));
                auto highestUnit = dynamic_cast<Unit *>(GlobalGameController->GetCardManager()
                    ->GetCardById(highestUnitId));
                auto lowestUnit  = dynamic_cast<Unit *>(GlobalGameController->GetCardManager()
                    ->GetCardById(LowestUnitId));


                // todo maybe we should select one unit randomly ...
                if (thisUnit->GetPower() > highestUnit->GetPower())
                {
                    highestUnitId = unit;
                }

                if (thisUnit->GetPower() < lowestUnit->GetPower())
                {
                    LowestUnitId = unit;
                }
            }
        }
    }

    auto highestUnit = dynamic_cast<Unit *>(GlobalGameController->GetCardManager()->GetCardById(highestUnitId));
    auto lowestUnit  = dynamic_cast<Unit *>(GlobalGameController->GetCardManager()->GetCardById(LowestUnitId));

    int damage = highestUnit->GetPower();
    if (damage > 10)
    {
        damage = 10;
    }

    highestUnit->DamageIgnoringArmorAndShield(damage);
    lowestUnit->GainPower(damage);
}
