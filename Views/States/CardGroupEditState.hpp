//
// Created on 2017/09/11 at 21:48.
//

#ifndef GWENT_CARDGROUPEDITSTATE_HPP
#define GWENT_CARDGROUPEDITSTATE_HPP

#include <QtWidgets/QWidget>
#include <QtWidgets/QSpinBox>
#include "IState.hpp"
#include "../../Models/Containers/CardGroup.hpp"


class CardGroup;

namespace Ui
{
class CardGroupEditState;
}


class CardGroupEditState : public QWidget, public IState
{
Q_OBJECT
public:
    CardGroupEditState(QWidget *parent);
protected:
    Ui::CardGroupEditState *CardGroupEditStateUi;

    CardGroup GetCardGroup();
    QString GetCardNameBySpinBoxRowColumn(int row, int column);

    QSpinBox *GetSpinBoxByCardName(const QString& cardName);
    void ResetAllToZero();
protected slots:
    void OnSave();
    void OnExport();
    void OnImport();
};


#endif //GWENT_CARDGROUPEDITSTATE_HPP
