//
// Created on 2017/09/03 at 15:43.
//

#include "Effect.hpp"


int Effect::GetSelectedUnit() const
{
    return SelectedUnit;
}


void Effect::SetSelectedUnit(int SelectedUnit)
{
    Effect::SelectedUnit = SelectedUnit;
}


const QString& Effect::GetSelectedLine() const
{
    return SelectedLine;
}


QString Effect::ToString()
{
    return QString("%1_%2").arg(CardId).arg(CardMetaInfo->GetName());
}


void Effect::SetSelectedLine(const QString& SelectedLine)
{
    Effect::SelectedLine = SelectedLine;
}


bool Effect::IsCardEffect(Card *card)
{
    return (dynamic_cast<Effect *>(card) != nullptr);
}


QString Effect::ToDisplayableString()
{
    return QString("[%1] %2").arg(CardId).arg(CardMetaInfo->GetName());
}


Effect::Effect(GameController *gameController)
    : Card(gameController)
{ }


void Effect::UpdateFromString(const QString& source)
{
    auto list = source.split('_');
    SetCardId(list[0].toInt());
}
