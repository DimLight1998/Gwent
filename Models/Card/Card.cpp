//
// Created on 2017/09/03 at 15:38.
//

#include "Card.hpp"


CardMeta *Card::GetCardMetaInfo() const
{
    return CardMetaInfo;
}


void Card::SetCardMetaInfo(CardMeta *CardMetaInfo)
{
    Card::CardMetaInfo = CardMetaInfo;
}


int Card::GetCardId() const
{
    return CardId;
}


void Card::SetCardId(int CardId)
{
    Card::CardId = CardId;
}
