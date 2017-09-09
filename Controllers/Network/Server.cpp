//
// Created on 2017/09/08 at 10:12.
//

#include <QtCore/QDataStream>
#include <QTcpSocket>
#include <QtCore/QTimer>
#include "Server.hpp"


quint16 Server::GetServerPort() const
{
    return ServerPort;
}


void Server::SetServerPort(quint16 ServerPort)
{
    Server::ServerPort = ServerPort;
}


void Server::StartServing()
{
    ServerServer = new QTcpServer();
    ServerServer->listen(QHostAddress::Any, ServerPort);
    qDebug() << "Server listening on" << ServerServer->serverAddress() << ServerServer->serverPort();
    connect(ServerServer, &QTcpServer::newConnection, this, &Server::HandleNewConnection);
}


void Server::HandleNewConnection()
{
    qDebug() << "Incoming connection";
    auto socket = ServerServer->nextPendingConnection();

    socket->waitForReadyRead(300);

    QDataStream in;
    in.setDevice(socket);
    in.setVersion(QDataStream::Qt_5_9);

    QString readMessage;
    in.startTransaction();
    if (!in.commitTransaction())
    {
        return;
    }
    in >> readMessage;

    qDebug() << readMessage;
    qDebug() << "Message from" << socket->peerAddress() << socket->peerPort();

    socket->close();

    if (readMessage.startsWith("REGISTER"))
    {
        auto address = readMessage.split('|')[1];
        auto port    = readMessage.split('|')[2].toInt();
        Clients.append(QPair<QString, quint16>(address, static_cast<const quint16&>(port)));

        qDebug() << "Current clients:";
        for (auto& i:Clients)
        {
            qDebug() << i;
        }
    }
    else
    {
        // broadcast
        Broadcast(readMessage);

        // handle
        HandleMessage(readMessage);
    }
}


void Server::Broadcast(const QString& readMessage)
{
    for (const auto& item:Clients)
    {
        auto address = item.first;
        auto port    = item.second;

        qDebug() << "Sending" << readMessage << "to" << address << port;

        auto *sendingSocket = new QTcpSocket(this);
        sendingSocket->connectToHost(address, port);

        QByteArray  block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_9);
        out << readMessage;

        sendingSocket->write(block);
        sendingSocket->disconnectFromHost();
        sendingSocket->close();

        QTimer::singleShot(2000, sendingSocket, &deleteLater);
    }
}


void Server::HandleMessage(const QString& message)
{
}
