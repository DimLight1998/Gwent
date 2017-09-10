//
// Created on 2017/09/03 at 15:38.
//

#ifndef GWENT_UNIT_HPP
#define GWENT_UNIT_HPP

#include "Card.hpp"


class Unit : public Card
{
public:
    Unit(GameController *gameController);
    /// \brief damage the unit, OnDestory will be called if the unit is dead
    /// \param damage the damage
    void Damage(int damage);

    /// \brief increase the unit's power
    /// \param gain the point of the gain
    void GainPower(int gain);

    /// \brief damage the unit, OnDestroy will bea called if the unit is dead,
    /// this function ignores unit's armor and shield
    /// \param damage damage to the unit
    void DamageIgnoringArmorAndShield(int damage);

    /// \brief increase the unit's armor
    /// \param gain the point of the gain
    void GainArmor(int gain);

    /// \brief destroy the unit directly and trigger its OnDestroy
    void Destroy();

    /// \brief test if the card is a unit
    /// \param card pointer to the card to be tested
    /// \return true if yes otherwise no
    static bool IsCardUnit(Card *card);


protected:
    int  Power     = 0;
    int  Armor     = 0;
    int  TimeCount = 0;
    bool HasShield = false;
public:
    int GetPower() const;
    void SetPower(int Power);
    int GetArmor() const;
    void SetArmor(int Armor);
    int GetTimeCount() const;
    void SetTimeCount(int TimeCount);
    bool IsHasShield() const;
    void SetHasShield(bool HasShield);
    const QString& GetSelectedLine() const;
    void SetSelectedLine(const QString& SelectedLine);
    int GetSelectedIndex() const;
    void SetSelectedIndex(int SelectedIndex);
    QString ToDisplayableString() override;
    QString ToString() override;
    void UpdateFromString(const QString& source) override;
protected:

    QString SelectedLine;
    int     SelectedIndex;
};


#endif //GWENT_UNIT_HPP
