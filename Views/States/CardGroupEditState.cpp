//
// Created on 2017/09/11 at 21:48.
//

#include <QtWidgets/QMessageBox>
#include <QDebug>
#include "CardGroupEditState.hpp"
#include "ui_CardGroupEditState.h"


CardGroupEditState::CardGroupEditState(QWidget *parent)
    : QWidget(parent)
{
    CardGroupEditStateUi = new Ui::CardGroupEditState();
    CardGroupEditStateUi->setupUi(this);

    auto *validator = new QRegExpValidator(QRegExp("^[a-zA-Z0-9_]+$"), this);
    CardGroupEditStateUi->lineEdit->setValidator(validator);

    connect(CardGroupEditStateUi->pushButton_4, &QPushButton::clicked, [this]
    {
      Base->SwitchToState("MainMenu");
    });

    connect(CardGroupEditStateUi->pushButton, &QPushButton::clicked, this, &CardGroupEditState::OnSave);
    connect(CardGroupEditStateUi->pushButton_2, &QPushButton::clicked, this, &CardGroupEditState::OnExport);
    connect(CardGroupEditStateUi->pushButton_3, &QPushButton::clicked, this, &CardGroupEditState::OnImport);
}


void CardGroupEditState::OnSave()
{
    auto    cardGroup = GetCardGroup();
    QString exportString;

    if (cardGroup.IsValid())
    {
        exportString = cardGroup.ToString();
    }
    else
    {
        QMessageBox::critical(this, tr("Error"), tr("Invalid card group"));
    }

    //todo
    QMessageBox::information(this, "Todo", "Save to server");
}


void CardGroupEditState::OnExport()
{
    auto    cardGroup = GetCardGroup();
    QString exportString;

    if (cardGroup.IsValid())
    {
        exportString = cardGroup.ToString();
    }
    else
    {
        QMessageBox::critical(this, tr("Error"), tr("Invalid card group"));
    }

    CardGroupEditStateUi->textEdit->setText(exportString);
}


void CardGroupEditState::OnImport()
{
    try
    {
        ResetAllToZero();
        CardGroup cardGroup;
        cardGroup.UpdateFromString(CardGroupEditStateUi->textEdit->toPlainText());
        for (const auto& item:cardGroup.GetCardMetaGroup())
        {
            auto spinBox = GetSpinBoxByCardName(item.GetName());
            spinBox->setValue(spinBox->value() + 1);
        }
    }
    catch (...)
    {
        QMessageBox::critical(this, tr("Error"), tr("Failed to import card group"));
    }
}


QString CardGroupEditState::GetCardNameBySpinBoxRowColumn(int row, int column)
{
    if (row == 1 && column == 0)
    { return "Dagon"; }
    if (row == 1 && column == 1)
    { return "Caranthir"; }
    if (row == 1 && column == 2)
    { return "GeEls"; }
    if (row == 1 && column == 3)
    { return "GeraltIgni"; }
    if (row == 1 && column == 4)
    { return "UnseenElder"; }
    if (row == 1 && column == 5)
    { return "WoodlandSpirit"; }
    if (row == 1 && column == 6)
    { return ""; }
    if (row == 1 && column == 7)
    { return ""; }
    if (row == 3 && column == 0)
    { return "BekkersTwistedMirror"; }
    if (row == 3 && column == 1)
    { return "CroneWhispess"; }
    if (row == 3 && column == 2)
    { return "CroneBrewess"; }
    if (row == 3 && column == 3)
    { return "CroneWeavess"; }
    if (row == 3 && column == 4)
    { return "Frightener"; }
    if (row == 3 && column == 5)
    { return "Roach"; }
    if (row == 3 && column == 6)
    { return "CommandersHorn"; }
    if (row == 3 && column == 7)
    { return ""; }
    if (row == 5 && column == 0)
    { return "Arachas"; }
    if (row == 5 && column == 1)
    { return "ArachasBehemoth"; }
    if (row == 5 && column == 2)
    { return "Archgriffin"; }
    if (row == 5 && column == 3)
    { return "BitingFrost"; }
    if (row == 5 && column == 4)
    { return "CelaenoHarpy"; }
    if (row == 5 && column == 5)
    { return "EarthElemental"; }
    if (row == 5 && column == 6)
    { return "FirstLight"; }
    if (row == 5 && column == 7)
    { return "Foglet"; }
    if (row == 7 && column == 0)
    { return "ImpenetrableFog"; }
    if (row == 7 && column == 1)
    { return "Lacerate"; }
    if (row == 7 && column == 2)
    { return "ThunderboltPotion"; }
    if (row == 7 && column == 3)
    { return "TorrentialRain"; }
    if (row == 7 && column == 4)
    { return "VranWarrior"; }
    if (row == 7 && column == 5)
    { return "WildHuntRider"; }
    if (row == 7 && column == 6)
    { return ""; }
    if (row == 7 && column == 7)
    { return ""; }
}


CardGroup CardGroupEditState::GetCardGroup()
{
    CardGroup cardGroup;

    for (int i = 0; i < CardGroupEditStateUi->SpinBox10->value(); i++)
    {
        auto cardName = GetCardNameBySpinBoxRowColumn(1, 0);
        if (cardName == "")
        { break; }
        auto meta = CardMeta::GetMetaByCardName(cardName);
        cardGroup.InsertIntoCardGroup(*meta);
        delete meta;
    }
    for (int i = 0; i < CardGroupEditStateUi->SpinBox11->value(); i++)
    {
        auto cardName = GetCardNameBySpinBoxRowColumn(1, 1);
        if (cardName == "")
        { break; }
        auto meta = CardMeta::GetMetaByCardName(cardName);
        cardGroup.InsertIntoCardGroup(*meta);
        delete meta;
    }
    for (int i = 0; i < CardGroupEditStateUi->SpinBox12->value(); i++)
    {
        auto cardName = GetCardNameBySpinBoxRowColumn(1, 2);
        if (cardName == "")
        { break; }
        auto meta = CardMeta::GetMetaByCardName(cardName);
        cardGroup.InsertIntoCardGroup(*meta);
        delete meta;
    }
    for (int i = 0; i < CardGroupEditStateUi->SpinBox13->value(); i++)
    {
        auto cardName = GetCardNameBySpinBoxRowColumn(1, 3);
        if (cardName == "")
        { break; }
        auto meta = CardMeta::GetMetaByCardName(cardName);
        cardGroup.InsertIntoCardGroup(*meta);
        delete meta;
    }
    for (int i = 0; i < CardGroupEditStateUi->SpinBox14->value(); i++)
    {
        auto cardName = GetCardNameBySpinBoxRowColumn(1, 4);
        if (cardName == "")
        { break; }
        auto meta = CardMeta::GetMetaByCardName(cardName);
        cardGroup.InsertIntoCardGroup(*meta);
        delete meta;
    }
    for (int i = 0; i < CardGroupEditStateUi->SpinBox15->value(); i++)
    {
        auto cardName = GetCardNameBySpinBoxRowColumn(1, 5);
        if (cardName == "")
        { break; }
        auto meta = CardMeta::GetMetaByCardName(cardName);
        cardGroup.InsertIntoCardGroup(*meta);
        delete meta;
    }
    for (int i = 0; i < CardGroupEditStateUi->SpinBox16->value(); i++)
    {
        auto cardName = GetCardNameBySpinBoxRowColumn(1, 6);
        if (cardName == "")
        { break; }
        auto meta = CardMeta::GetMetaByCardName(cardName);
        cardGroup.InsertIntoCardGroup(*meta);
        delete meta;
    }
    for (int i = 0; i < CardGroupEditStateUi->SpinBox17->value(); i++)
    {
        auto cardName = GetCardNameBySpinBoxRowColumn(1, 7);
        if (cardName == "")
        { break; }
        auto meta = CardMeta::GetMetaByCardName(cardName);
        cardGroup.InsertIntoCardGroup(*meta);
        delete meta;
    }
    for (int i = 0; i < CardGroupEditStateUi->SpinBox30->value(); i++)
    {
        auto cardName = GetCardNameBySpinBoxRowColumn(3, 0);
        if (cardName == "")
        { break; }
        auto meta = CardMeta::GetMetaByCardName(cardName);
        cardGroup.InsertIntoCardGroup(*meta);
        delete meta;
    }
    for (int i = 0; i < CardGroupEditStateUi->SpinBox31->value(); i++)
    {
        auto cardName = GetCardNameBySpinBoxRowColumn(3, 1);
        if (cardName == "")
        { break; }
        auto meta = CardMeta::GetMetaByCardName(cardName);
        cardGroup.InsertIntoCardGroup(*meta);
        delete meta;
    }
    for (int i = 0; i < CardGroupEditStateUi->SpinBox32->value(); i++)
    {
        auto cardName = GetCardNameBySpinBoxRowColumn(3, 2);
        if (cardName == "")
        { break; }
        auto meta = CardMeta::GetMetaByCardName(cardName);
        cardGroup.InsertIntoCardGroup(*meta);
        delete meta;
    }
    for (int i = 0; i < CardGroupEditStateUi->SpinBox33->value(); i++)
    {
        auto cardName = GetCardNameBySpinBoxRowColumn(3, 3);
        if (cardName == "")
        { break; }
        auto meta = CardMeta::GetMetaByCardName(cardName);
        cardGroup.InsertIntoCardGroup(*meta);
        delete meta;
    }
    for (int i = 0; i < CardGroupEditStateUi->SpinBox34->value(); i++)
    {
        auto cardName = GetCardNameBySpinBoxRowColumn(3, 4);
        if (cardName == "")
        { break; }
        auto meta = CardMeta::GetMetaByCardName(cardName);
        cardGroup.InsertIntoCardGroup(*meta);
        delete meta;
    }
    for (int i = 0; i < CardGroupEditStateUi->SpinBox35->value(); i++)
    {
        auto cardName = GetCardNameBySpinBoxRowColumn(3, 5);
        if (cardName == "")
        { break; }
        auto meta = CardMeta::GetMetaByCardName(cardName);
        cardGroup.InsertIntoCardGroup(*meta);
        delete meta;
    }
    for (int i = 0; i < CardGroupEditStateUi->SpinBox36->value(); i++)
    {
        auto cardName = GetCardNameBySpinBoxRowColumn(3, 6);
        if (cardName == "")
        { break; }
        auto meta = CardMeta::GetMetaByCardName(cardName);
        cardGroup.InsertIntoCardGroup(*meta);
        delete meta;
    }
    for (int i = 0; i < CardGroupEditStateUi->SpinBox37->value(); i++)
    {
        auto cardName = GetCardNameBySpinBoxRowColumn(3, 7);
        if (cardName == "")
        { break; }
        auto meta = CardMeta::GetMetaByCardName(cardName);
        cardGroup.InsertIntoCardGroup(*meta);
        delete meta;
    }
    for (int i = 0; i < CardGroupEditStateUi->SpinBox50->value(); i++)
    {
        auto cardName = GetCardNameBySpinBoxRowColumn(5, 0);
        if (cardName == "")
        { break; }
        auto meta = CardMeta::GetMetaByCardName(cardName);
        cardGroup.InsertIntoCardGroup(*meta);
        delete meta;
    }
    for (int i = 0; i < CardGroupEditStateUi->SpinBox51->value(); i++)
    {
        auto cardName = GetCardNameBySpinBoxRowColumn(5, 1);
        if (cardName == "")
        { break; }
        auto meta = CardMeta::GetMetaByCardName(cardName);
        cardGroup.InsertIntoCardGroup(*meta);
        delete meta;
    }
    for (int i = 0; i < CardGroupEditStateUi->SpinBox52->value(); i++)
    {
        auto cardName = GetCardNameBySpinBoxRowColumn(5, 2);
        if (cardName == "")
        { break; }
        auto meta = CardMeta::GetMetaByCardName(cardName);
        cardGroup.InsertIntoCardGroup(*meta);
        delete meta;
    }
    for (int i = 0; i < CardGroupEditStateUi->SpinBox53->value(); i++)
    {
        auto cardName = GetCardNameBySpinBoxRowColumn(5, 3);
        if (cardName == "")
        { break; }
        auto meta = CardMeta::GetMetaByCardName(cardName);
        cardGroup.InsertIntoCardGroup(*meta);
        delete meta;
    }
    for (int i = 0; i < CardGroupEditStateUi->SpinBox54->value(); i++)
    {
        auto cardName = GetCardNameBySpinBoxRowColumn(5, 4);
        if (cardName == "")
        { break; }
        auto meta = CardMeta::GetMetaByCardName(cardName);
        cardGroup.InsertIntoCardGroup(*meta);
        delete meta;
    }
    for (int i = 0; i < CardGroupEditStateUi->SpinBox55->value(); i++)
    {
        auto cardName = GetCardNameBySpinBoxRowColumn(5, 5);
        if (cardName == "")
        { break; }
        auto meta = CardMeta::GetMetaByCardName(cardName);
        cardGroup.InsertIntoCardGroup(*meta);
        delete meta;
    }
    for (int i = 0; i < CardGroupEditStateUi->SpinBox56->value(); i++)
    {
        auto cardName = GetCardNameBySpinBoxRowColumn(5, 6);
        if (cardName == "")
        { break; }
        auto meta = CardMeta::GetMetaByCardName(cardName);
        cardGroup.InsertIntoCardGroup(*meta);
        delete meta;
    }
    for (int i = 0; i < CardGroupEditStateUi->SpinBox57->value(); i++)
    {
        auto cardName = GetCardNameBySpinBoxRowColumn(5, 7);
        if (cardName == "")
        { break; }
        auto meta = CardMeta::GetMetaByCardName(cardName);
        cardGroup.InsertIntoCardGroup(*meta);
        delete meta;
    }
    for (int i = 0; i < CardGroupEditStateUi->SpinBox70->value(); i++)
    {
        auto cardName = GetCardNameBySpinBoxRowColumn(7, 0);
        if (cardName == "")
        { break; }
        auto meta = CardMeta::GetMetaByCardName(cardName);
        cardGroup.InsertIntoCardGroup(*meta);
        delete meta;
    }
    for (int i = 0; i < CardGroupEditStateUi->SpinBox71->value(); i++)
    {
        auto cardName = GetCardNameBySpinBoxRowColumn(7, 1);
        if (cardName == "")
        { break; }
        auto meta = CardMeta::GetMetaByCardName(cardName);
        cardGroup.InsertIntoCardGroup(*meta);
        delete meta;
    }
    for (int i = 0; i < CardGroupEditStateUi->SpinBox72->value(); i++)
    {
        auto cardName = GetCardNameBySpinBoxRowColumn(7, 2);
        if (cardName == "")
        { break; }
        auto meta = CardMeta::GetMetaByCardName(cardName);
        cardGroup.InsertIntoCardGroup(*meta);
        delete meta;
    }
    for (int i = 0; i < CardGroupEditStateUi->SpinBox73->value(); i++)
    {
        auto cardName = GetCardNameBySpinBoxRowColumn(7, 3);
        if (cardName == "")
        { break; }
        auto meta = CardMeta::GetMetaByCardName(cardName);
        cardGroup.InsertIntoCardGroup(*meta);
        delete meta;
    }
    for (int i = 0; i < CardGroupEditStateUi->SpinBox74->value(); i++)
    {
        auto cardName = GetCardNameBySpinBoxRowColumn(7, 4);
        if (cardName == "")
        { break; }
        auto meta = CardMeta::GetMetaByCardName(cardName);
        cardGroup.InsertIntoCardGroup(*meta);
        delete meta;
    }
    for (int i = 0; i < CardGroupEditStateUi->SpinBox75->value(); i++)
    {
        auto cardName = GetCardNameBySpinBoxRowColumn(7, 5);
        if (cardName == "")
        { break; }
        auto meta = CardMeta::GetMetaByCardName(cardName);
        cardGroup.InsertIntoCardGroup(*meta);
        delete meta;
    }
    for (int i = 0; i < CardGroupEditStateUi->SpinBox76->value(); i++)
    {
        auto cardName = GetCardNameBySpinBoxRowColumn(7, 6);
        if (cardName == "")
        { break; }
        auto meta = CardMeta::GetMetaByCardName(cardName);
        cardGroup.InsertIntoCardGroup(*meta);
        delete meta;
    }
    for (int i = 0; i < CardGroupEditStateUi->SpinBox77->value(); i++)
    {
        auto cardName = GetCardNameBySpinBoxRowColumn(7, 7);
        if (cardName == "")
        { break; }
        auto meta = CardMeta::GetMetaByCardName(cardName);
        cardGroup.InsertIntoCardGroup(*meta);
        delete meta;
    }

    return cardGroup;
}


QSpinBox *CardGroupEditState::GetSpinBoxByCardName(const QString& cardName)
{
    if (cardName == "Dagon")
    { return CardGroupEditStateUi->SpinBox10; }
    if (cardName == "Caranthir")
    { return CardGroupEditStateUi->SpinBox11; }
    if (cardName == "GeEls")
    { return CardGroupEditStateUi->SpinBox12; }
    if (cardName == "GeraltIgni")
    { return CardGroupEditStateUi->SpinBox13; }
    if (cardName == "UnseenElder")
    { return CardGroupEditStateUi->SpinBox14; }
    if (cardName == "WoodlandSpirit")
    { return CardGroupEditStateUi->SpinBox15; }
    if (cardName == "BekkersTwistedMirror")
    { return CardGroupEditStateUi->SpinBox30; }
    if (cardName == "CroneWhispess")
    { return CardGroupEditStateUi->SpinBox31; }
    if (cardName == "CroneBrewess")
    { return CardGroupEditStateUi->SpinBox32; }
    if (cardName == "CroneWeavess")
    { return CardGroupEditStateUi->SpinBox33; }
    if (cardName == "Frightener")
    { return CardGroupEditStateUi->SpinBox34; }
    if (cardName == "Roach")
    { return CardGroupEditStateUi->SpinBox35; }
    if (cardName == "CommandersHorn")
    { return CardGroupEditStateUi->SpinBox36; }
    if (cardName == "Arachas")
    { return CardGroupEditStateUi->SpinBox50; }
    if (cardName == "ArachasBehemoth")
    { return CardGroupEditStateUi->SpinBox51; }
    if (cardName == "Archgriffin")
    { return CardGroupEditStateUi->SpinBox52; }
    if (cardName == "BitingFrost")
    { return CardGroupEditStateUi->SpinBox53; }
    if (cardName == "CelaenoHarpy")
    { return CardGroupEditStateUi->SpinBox54; }
    if (cardName == "EarthElemental")
    { return CardGroupEditStateUi->SpinBox55; }
    if (cardName == "FirstLight")
    { return CardGroupEditStateUi->SpinBox56; }
    if (cardName == "Foglet")
    { return CardGroupEditStateUi->SpinBox57; }
    if (cardName == "ImpenetrableFog")
    { return CardGroupEditStateUi->SpinBox70; }
    if (cardName == "Lacerate")
    { return CardGroupEditStateUi->SpinBox71; }
    if (cardName == "ThunderboltPotion")
    { return CardGroupEditStateUi->SpinBox72; }
    if (cardName == "TorrentialRain")
    { return CardGroupEditStateUi->SpinBox73; }
    if (cardName == "VranWarrior")
    { return CardGroupEditStateUi->SpinBox74; }
    if (cardName == "WildHuntRider")
    { return CardGroupEditStateUi->SpinBox75; }
}


void CardGroupEditState::ResetAllToZero()
{
    CardGroupEditStateUi->SpinBox10->setValue(0);
    CardGroupEditStateUi->SpinBox11->setValue(0);
    CardGroupEditStateUi->SpinBox12->setValue(0);
    CardGroupEditStateUi->SpinBox13->setValue(0);
    CardGroupEditStateUi->SpinBox14->setValue(0);
    CardGroupEditStateUi->SpinBox15->setValue(0);
    CardGroupEditStateUi->SpinBox16->setValue(0);
    CardGroupEditStateUi->SpinBox17->setValue(0);
    CardGroupEditStateUi->SpinBox30->setValue(0);
    CardGroupEditStateUi->SpinBox31->setValue(0);
    CardGroupEditStateUi->SpinBox32->setValue(0);
    CardGroupEditStateUi->SpinBox33->setValue(0);
    CardGroupEditStateUi->SpinBox34->setValue(0);
    CardGroupEditStateUi->SpinBox35->setValue(0);
    CardGroupEditStateUi->SpinBox36->setValue(0);
    CardGroupEditStateUi->SpinBox37->setValue(0);
    CardGroupEditStateUi->SpinBox50->setValue(0);
    CardGroupEditStateUi->SpinBox51->setValue(0);
    CardGroupEditStateUi->SpinBox52->setValue(0);
    CardGroupEditStateUi->SpinBox53->setValue(0);
    CardGroupEditStateUi->SpinBox54->setValue(0);
    CardGroupEditStateUi->SpinBox55->setValue(0);
    CardGroupEditStateUi->SpinBox56->setValue(0);
    CardGroupEditStateUi->SpinBox57->setValue(0);
    CardGroupEditStateUi->SpinBox70->setValue(0);
    CardGroupEditStateUi->SpinBox71->setValue(0);
    CardGroupEditStateUi->SpinBox72->setValue(0);
    CardGroupEditStateUi->SpinBox73->setValue(0);
    CardGroupEditStateUi->SpinBox74->setValue(0);
    CardGroupEditStateUi->SpinBox75->setValue(0);
    CardGroupEditStateUi->SpinBox76->setValue(0);
    CardGroupEditStateUi->SpinBox77->setValue(0);
}

