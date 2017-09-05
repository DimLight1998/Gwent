//
// Created on 2017/09/05 at 09:58.
//

#ifndef GWENT_INTERACTINGCONTROLLER_HPP
#define GWENT_INTERACTINGCONTROLLER_HPP

#include "../Models/Meta/CardMeta.hpp"
#include <QVector>


class GameController;


class InteractingController
{
public:
    GameController *GetController() const;
    void SetController(GameController *Controller);

    /// \brief get selected card from existing cards, like select one card from the deck
    /// \param existingCardsId the vector of cards chosen from
    /// \return id of the chosen card
    /// \example
    /// \code
    /// QVector<int> vec;
    /// for(auto i: deck)
    /// {
    ///     vec.append(i);
    /// }
    ///
    /// auto ret = GetSelectedCardFromExistingCards(vec);
    /// \endcode
    /// now we have what the player choose
    int GetSelectedCardFromExistingCards(const QVector<int>& existingCardsId);

    /// \brief get selected card from non-existing cards, like select one from three weather (Dagon)
    /// \param spawningCardsMeta the vector of cards chosen from
    /// \return CardMeta of the chosen card
    /// \example
    /// \code
    /// QVector<CardMeta> cardMeta = QVector<CardMeta>
    /// ({CardMeta::GetMetaByCardName("BitingFrost"), CardMeta::GetMetaByCardName("ImpenetrableFog")});
    /// auto selected = GetSelectedCardFromSpanningCards(cardMeta);
    /// for(auto i:cardMeta)
    /// {
    ///     delete i;
    /// }
    ///
    /// \endcode
    /// now we have what the player choose
    CardMeta GetSelectedCardFromSpanningCards(const QVector<CardMeta *>& spawningCardsMeta);

    /// \brief wait until the player made a global selection
    void GetGlobalSelection();

    /// \brief get an selected card from the battle field
    /// \return id of the card
    int GetSelectedCardFromBattleField();

    /// \brief get an selected card from the battle field, but only cards with id in filter can be chosen
    /// \param filter vector of id, only cards having the id in this can be chosen
    /// \return id of the chosen card
    int GetSelectedCardFromBattleField(const QVector<int>& filter);

    /// \brief wait until player choose a valid location to deploy a unit
    /// \param [out] deployBattleLine battle line of deployment, in format (Enemy|Allied)(Melee|Siege|Ranged)
    /// \param [out] deployIndex index of the deployment
    void GetSelectedUnitDeployLocation(QString& deployBattleLine, int& deployIndex);

    /// \brief wait until player choose a valid line to deploy a battle line
    /// \return battle line of deployment, in format (Enemy|Allied)(Melee|Siege|Ranged)
    QString GetSelectedEffectDeployBattleLine();

protected:
    GameController *Controller;
};


#endif //GWENT_INTERACTINGCONTROLLER_HPP