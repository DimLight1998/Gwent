//
// Created on 2017/09/12 at 17:38.
//

#ifndef GWENT_CARDBUTTON_HPP
#define GWENT_CARDBUTTON_HPP

#include <QtWidgets/QPushButton>
#include "../../Models/Containers/CardManager.hpp"


class CardButton : public QPushButton
{
Q_OBJECT
protected:
    int         CardId;
    CardManager *Manager;
protected:
    void paintEvent(QPaintEvent *event) override;
public:
    CardButton(QWidget *parent, int CardId, CardManager *Manager);
    int GetCardId() const;
    void SetCardId(int CardId);
    CardManager *GetManager() const;
    void SetManager(CardManager *Manager);
private:
};


#endif //GWENT_CARDBUTTON_HPP
