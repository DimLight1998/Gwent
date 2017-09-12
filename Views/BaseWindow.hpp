//
// Created on 2017/09/11 at 15:32.
//

#ifndef GWENT_BASEWINDOW_HPP
#define GWENT_BASEWINDOW_HPP

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStackedWidget>
#include <QtCore/QMap>
#include <QVariant>


class BaseWindow : public QMainWindow
{
Q_OBJECT
public:
    BaseWindow();

protected:
    QStackedWidget *StackedWidget;
public:
    QStackedWidget *GetStackedWidget() const;

    void SwitchToState(const QString& stateName);

    QVariant GetSharedData(const QString& index);
    void SetSharedData(const QString& index, QVariant data);

protected:
    bool    IsLoggedIn = false;
    QString Username   = "";

    QMap<QString, QVariant> SharedData;
};


#endif //GWENT_BASEWINDOW_HPP
