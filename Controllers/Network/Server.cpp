//
// Created on 2017/09/08 at 10:12.
//

#include <QtCore/QDataStream>
#include <QTcpSocket>
#include <QtCore/QTimer>
#include <QtCore/QEventLoop>
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

    QEventLoop eventLoop;
    connect(socket, &QTcpSocket::readyRead, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    QDataStream in;
    in.setDevice(socket);
    in.setVersion(QDataStream::Qt_5_9);

    QString readMessage;
    in.startTransaction();
    in >> readMessage;

    if (!in.commitTransaction())
    {
        return;
    }

    //    QEventLoop eventLoop;
    //    QTimer::singleShot(1000, &eventLoop, &QEventLoop::quit);
    //    eventLoop.exec();

    if (readMessage == "")
    {
        qDebug() << "***************ERROR Server reading error";
    }
    qDebug() << "Message from" << socket->peerAddress() << socket->peerPort();

    socket->close();

    if (readMessage.startsWith("REGISTER"))
    {
        auto address = readMessage.split('|', QString::SkipEmptyParts)[1];
        auto port    = readMessage.split('|', QString::SkipEmptyParts)[2].toInt();
        Clients.append(QPair<QString, quint16>(address, static_cast<const quint16&>(port)));
    }
    else if (readMessage.startsWith("UNREGISTER"))
    {
        auto address = readMessage.split('|', QString::SkipEmptyParts)[1];
        auto port    = readMessage.split('|', QString::SkipEmptyParts)[2].toInt();

        for (int i = 0; i < Clients.size(); i++)
        {
            if (Clients[i].first == address && Clients[i].second == static_cast<const quint16&>(port))
            {
                Clients.remove(i);
                break;
            }
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

        auto *sendingSocket = new QTcpSocket(this);
        sendingSocket->connectToHost(address, port);

        QByteArray  block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_9);
        out << readMessage;

        auto length = block.length();
        auto sent   = 0;

        sendingSocket->write(block);

        QEventLoop eventLoop;
        connect(sendingSocket, &QTcpSocket::bytesWritten, [&eventLoop, &sent, length](qint64 payloadLength)
        {
          sent += payloadLength;
          if (sent >= length)
          {
              eventLoop.exit(0);
          }
        });
        eventLoop.exec();

        sendingSocket->disconnectFromHost();
        sendingSocket->close();

        QTimer::singleShot(2000, sendingSocket, &QTcpSocket::deleteLater);
    }
}


void Server::HandleMessage(const QString& message)
{
}
