//
// Created on 2017/09/03 at 15:38.
//

#include "Card.hpp"
#include "../Assets/Units/HarpyEgg.hpp"
#include "../Assets/Units/HarpyHatchling.hpp"


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


Card::~Card()
{
    delete CardMetaInfo;
}


Card *Card::SpanCardByName(const QString& name)
{
    if (name == "HarpyEgg")
    {
        return new HarpyEgg();
    }

    if (name == "HarpyHatchling")
    {
        return new HarpyHatchling();
    }
}


void Card::OnDeploy()
{
}


void Card::OnDestroy()
{
}


void Card::OnDeathWish()
{
}


void Card::RoundUpdate()
{
}
