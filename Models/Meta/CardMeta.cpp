//
// Created on 2017/09/03 at 14:06.
//

#include "CardMeta.hpp"
#include "EffectsMeta.hpp"


CardMeta::CardTypeEnum CardMeta::GetCardType() const
{
    return _cardType;
}


void CardMeta::SetCardType(CardMeta::CardTypeEnum cardType)
{
    _cardType = cardType;
}


const QString& CardMeta::GetName() const
{
    return _name;
}


void CardMeta::SetName(const QString& name)
{
    _name = name;
}


const QString& CardMeta::GetDescription() const
{
    return _description;
}


void CardMeta::SetDescription(const QString& description)
{
    _description = description;
}


const QString& CardMeta::GetPictureResourcePath() const
{
    return _pictureResourcePath;
}


void CardMeta::SetPictureResourcePath(const QString& pictureResourcePath)
{
    _pictureResourcePath = pictureResourcePath;
}


CardMeta *CardMeta::GetMetaByCardName(const QString& name)
{
    if (name == "FirstLight")
    {
        auto cardMeta = new EffectsMeta();
        cardMeta->SetName("FirstLight");
        cardMeta->SetCardType(CardTypeEnum::Bronze);
        cardMeta->SetDescription(
            "Spawn Clear Skies or Rally."
        );
        cardMeta->SetPictureResourcePath(""); // todo fill this
        cardMeta->SetDeployType(EffectsMeta::DeployTypeEnum::LineSelect); // todo this card have to select another card

        return cardMeta;
    }

    if (name == "BitingFrost")
    {
        auto cardMeta = new EffectsMeta();
        cardMeta->SetName("BitingFrost");
        cardMeta->SetCardType(CardTypeEnum::Bronze);
        cardMeta->SetDescription(
            "Apply Frost to a row on your opponent's side.\n"
                "Frost: Every turn, at the start of your turn, Damage the Lowest Unit on the row by 2."
        );
        cardMeta->SetPictureResourcePath("");// todo fill this
        cardMeta->SetDeployType(EffectsMeta::DeployTypeEnum::LineSelect);

        return cardMeta;
    }

    throw 263784;
}
