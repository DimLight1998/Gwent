//
// Created on 2017/09/03 at 16:09.
//

#ifndef GWENT_CARDGROUP_HPP
#define GWENT_CARDGROUP_HPP

#include <QVector>
#include "../Meta/CardMeta.hpp"


class CardGroup
{
private:
    QVector<CardMeta> _cardMetaGroup;

public:
    /// \brief check if this is a valid card group
    /// \return true if it's a valid card group, else false
    bool Validate();
};


#endif //GWENT_CARDGROUP_HPP
