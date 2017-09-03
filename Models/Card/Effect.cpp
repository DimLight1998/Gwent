//
// Created on 2017/09/03 at 15:43.
//

#include "Effect.hpp"


Unit *Effect::GetSelectedUnit() const
{
    return SelectedUnit;
}


void Effect::SetSelectedUnit(Unit *SelectedUnit)
{
    Effect::SelectedUnit = SelectedUnit;
}


BattleLine *Effect::GetSelectedLine() const
{
    return SelectedLine;
}


void Effect::SetSelectedLine(BattleLine *SelectedLine)
{
    Effect::SelectedLine = SelectedLine;
}
