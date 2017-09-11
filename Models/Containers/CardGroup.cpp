//
// Created on 2017/09/03 at 16:09.
//

#include "CardGroup.hpp"


bool CardGroup::IsValid()
{
    if (_cardMetaGroup.size() > 40 || _cardMetaGroup.size() < 25)
    {
        return false;
    }

    int silverCount = 0;
    int goldCount   = 0;
    int leaderCount = 0;

    for (const auto& i:_cardMetaGroup)
    {
        if (i.GetCardType() == CardMeta::CardTypeEnum::Silver)
        {
            silverCount++;
        }
        if (i.GetCardType() == CardMeta::CardTypeEnum::Gold)
        {
            goldCount++;
        }
        if (i.GetCardType() == CardMeta::CardTypeEnum::Leader)
        {
            leaderCount++;
        }
    }

    if (silverCount > 6 || goldCount > 4 || leaderCount != 1)
    {
        return false;
    }

    for (const auto& i:_cardMetaGroup)
    {
        const auto& name = i.GetName();
        int sameNameCount = 0;
        int sameNameLimit = 0;

        switch (i.GetCardType())
        {
        case CardMeta::CardTypeEnum::Bronze:sameNameLimit = 3;
            break;
        case CardMeta::CardTypeEnum::Silver:
        case CardMeta::CardTypeEnum::Gold:
        case CardMeta::CardTypeEnum::Leader:sameNameLimit = 1;
            break;
        }

        for (const auto& j:_cardMetaGroup)
        {
            if (j.GetName() == name)
            {
                sameNameCount++;
            }
        }

        if (sameNameCount > sameNameLimit)
        {
            return false;
        }
    }

    return true;
}


const QVector<CardMeta>& CardGroup::GetCardMetaGroup() const
{
    return _cardMetaGroup;
}


void CardGroup::InsertIntoCardGroup(CardMeta cardMeta)
{
    _cardMetaGroup.insert(0, cardMeta);
}


QString CardGroup::ToString() const
{
    QStringList stringList;
    for (const auto& item:_cardMetaGroup)
    {
        stringList.append(item.GetName());
    }

    return stringList.join('|');
}


void CardGroup::UpdateFromString(const QString& source)
{
    _cardMetaGroup.clear();
    auto stringList = source.split('|');
    for (const auto& item:stringList)
    {
        auto meta = CardMeta::GetMetaByCardName(item);
        _cardMetaGroup.append(*meta);
        delete meta;
    }
}
