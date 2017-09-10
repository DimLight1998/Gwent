//
// Created on 2017/09/03 at 16:12.
//

#ifndef GWENT_CARDCONTAINER_HPP
#define GWENT_CARDCONTAINER_HPP

#include <QVector>
#include "../Card/Card.hpp"


class CardContainer
{
protected:
    QVector<int> Cards; ///< stores id of the cards
public:
    const QVector<int>& GetCards() const;
    CardContainer();

    /// \brief remove the card of id
    /// \param id id of the card
    /// \throw 849532 if id incorrect
    void RemoveCardOfId(int id);

    /// \brief test if the card container contains the card
    /// \param id id of the card
    /// \return true if yes, otherwise no
    bool IsCardContainerContainingCard(int id);

    /// \brief this function can insert a card to the container
    /// \param cardId id of the card
    /// \param index the index of the inserting position, ranged from 0 to Cards.size()
    /// \throw 233333 if index not correct
    void InsertCard(int cardId, int index);

    /// \brief clear the card container, this is harmless because it just stores numbers
    void ClearCardContainer();

    /// \brief convert the card container to a string to synchronize with separator %
    /// \return a string which can represent the status of the card container
    QString ToString();

    /// \brief build the card container from a string
    /// \param source the string defining the card container,
    /// in format 1%2%3%4
    void UpdateFromString(const QString& source);
};


#endif //GWENT_CARDCONTAINER_HPP
