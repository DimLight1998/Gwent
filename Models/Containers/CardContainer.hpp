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

    /// \brief remove the card of id
    /// \param id id of the card
    /// \throw 849532 if id incorrect
    void RemoveCardOfId(int id);

    /// \brief test if the card container contains the card
    /// \param id id of the card
    /// \return true if yes, otherwise no
    bool IsCardContainerContainingCard(int id);
};


#endif //GWENT_CARDCONTAINER_HPP
