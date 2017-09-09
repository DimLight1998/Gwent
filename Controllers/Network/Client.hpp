//
// Created on 2017/09/08 at 09:44.
//

#ifndef GWENT_CLIENT_HPP
#define GWENT_CLIENT_HPP

#include <QTcpServer>
#include <QTcpSocket>


class Client : public QObject
{
Q_OBJECT
public:
    void RegisterToHost();

    void SendMessage(const QString& message);
protected:
    QString ServerAddress;
    quint16 ServerPort;

    QTcpServer *ClientServer = nullptr;

    QString GetLocalAddress();

    virtual void HandleMessage(const QString& message);
public:
    const QString& GetServerAddress() const;
    void SetRemoteServerAddress(const QString& ServerAddress);
    quint16 GetServerPort() const;
    void SetRemoteServerPort(quint16 ServerPort);
protected slots:
    void HandleNewConnection();
};


#endif //GWENT_CLIENT_HPP
