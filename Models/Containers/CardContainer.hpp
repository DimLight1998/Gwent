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
};


#endif //GWENT_CARDCONTAINER_HPP
