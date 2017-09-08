//
// Created on 2017/09/08 at 10:12.
//

#ifndef GWENT_SERVER_HPP
#define GWENT_SERVER_HPP

#include <QtCore/QObject>
#include <QtNetwork/QTcpServer>


class Server : public QObject
{
Q_OBJECT
public:
    void StartServing();
protected:
    QTcpServer *ServerServer;

    quint16 ServerPort;

    QVector<QPair<QString, quint16>> Clients;
public:
    quint16 GetServerPort() const;
    void SetServerPort(quint16 ServerPort);

protected:
    void HandleNewConnection();
};


#endif //GWENT_SERVER_HPP
