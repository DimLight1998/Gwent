//
// Created on 2017/09/03 at 14:06.
//

#ifndef GWENT_CARDMETA_HPP
#define GWENT_CARDMETA_HPP

#include <QtCore/QString>


class CardMeta
{
public:
    enum class CardTypeEnum
    {
        Bronze, Silver, Gold, Leader
    };

private:
    CardTypeEnum _cardType;
    QString      _name;
    QString      _description;
    QString      _pictureResourcePath;

public:
    CardTypeEnum GetCardType() const;
    void SetCardType(CardTypeEnum cardType);
    const QString& GetName() const;
    void SetName(const QString& name);
    const QString& GetDescription() const;
    void SetDescription(const QString& description);
    const QString& GetPictureResourcePath() const;
    void SetPictureResourcePath(const QString& pictureResourcePath);

    //! \brief get the meta-info about the card
    //! \param name name of the card
    //! \return pointer to the card meta-info
    //! \warning this function will allocate a new CardMeta object, you should delete the function by yourself
    //! \note all other data is based on this function
    //! \throw 263784 if name is incorrect
    static CardMeta *GetMetaByCardName(const QString& name);
};


#endif //GWENT_CARDMETA_HPP
