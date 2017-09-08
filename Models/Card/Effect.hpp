//
// Created on 2017/09/03 at 15:43.
//

#ifndef GWENT_EFFECT_HPP
#define GWENT_EFFECT_HPP

#include "Card.hpp"
#include "Unit.hpp"
#include "../Containers/BattleLine.hpp"


class Effect : public Card
{
protected:
    int     SelectedUnit = 0; ///< used for effects unit select
    QString SelectedLine = ""; ///< used for effects line select

public:
    Effect(GameController *gameController);
    int GetSelectedUnit() const;
    void SetSelectedUnit(int SelectedUnit);
    const QString& GetSelectedLine() const;
    void SetSelectedLine(const QString& SelectedLine);

    /// \brief test if the card is a effect
    /// \param card pointer to the card to be tested
    /// \return true if yes else no
    static bool IsCardEffect(Card *card);
    QString ToString() override;
};


#endif //GWENT_EFFECT_HPP
