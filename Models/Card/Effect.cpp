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


void Effect::SetSelectedLine(const QString& SelectedLine)
{
    Effect::SelectedLine = SelectedLine;
}
