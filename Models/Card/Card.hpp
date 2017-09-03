//
// Created on 2017/09/03 at 15:38.
//

#ifndef GWENT_CARD_HPP
#define GWENT_CARD_HPP

#include "../Meta/CardMeta.hpp"


class Card
{
public:
    //! \brief triggered when the card is deployed
    virtual void OnDeploy() = 0;

    //! \brief triggered when the card is destroyed
    //! \note This function will handle moving the card to the grave and trigger its death wish
    virtual void OnDestroy() = 0;

    //! \bried triggered when the death wish of the unit is triggered
    //! \note The reason why I use this function is because some unit can trigger death wish but they don't need to die
    virtual void OnDeathWish() = 0;
protected:
    CardMeta *CardMetaInfo; //<! stores meta-info of the card, not for sharing
};


#endif //GWENT_CARD_HPP
