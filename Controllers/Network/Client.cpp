//
// Created on 2017/09/08 at 09:44.
//

#include <QtCore/QDataStream>
#include <QtNetwork/QNetworkInterface>
#include <QtCore/QTimer>
#include <QtCore/QEventLoop>
#include <QTcpSocket>
#include "Client.hpp"


void Client::RegisterToHost()
{
    ClientServer = new QTcpServer(this);
    ClientServer->listen(QHostAddress::Any, 0);

    qDebug() << "Server on" << ClientServer->serverAddress() << ClientServer->serverPort();

    connect(ClientServer, &QTcpServer::newConnection, this, &Client::HandleNewConnection);

    auto localHost = GetLocalAddress();
    auto port      = ClientServer->serverPort();

    auto message = "REGISTER|" + localHost + "|" + QString::number(port);
    qDebug() << "Registering" << message;
    SendMessage(message);
    qDebug() << "Registering information sent";
}


void Client::SendMessage(const QString& message)
{
    auto *sendingSocket = new QTcpSocket(this);
    sendingSocket->connectToHost(ServerAddress, ServerPort);

    QByteArray  block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_9);
    out << message;

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


const QString& Client::GetServerAddress() const
{
    return ServerAddress;
}


void Client::SetRemoteServerAddress(const QString& ServerAddress)
{
    Client::ServerAddress = ServerAddress;
}


quint16 Client::GetServerPort() const
{
    return ServerPort;
}


void Client::SetRemoteServerPort(quint16 ServerPort)
{
    Client::ServerPort = ServerPort;
}


void Client::HandleNewConnection()
{
    qDebug() << "Client new connection received";

    auto socket = ClientServer->nextPendingConnection();

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
    //    QTimer::singleShot(100, &eventLoop, &QEventLoop::quit);
    //    eventLoop.exec();

    if (readMessage == "")
    {
        qDebug() << "***************ERROR client reading error";
    }

    HandleMessage(readMessage);
}


QString Client::GetLocalAddress()
{
    auto ipAddress = QNetworkInterface::allAddresses();

    for (const auto& item:ipAddress)
    {
        if (item != QHostAddress::LocalHost && item.toIPv4Address())
        {
            // Ignore Windows reserved(?)
            if (item.toString().startsWith("169.254"))
            {
                continue;
            }

            // On my computer I need to ignore VirtualBox Host-Only Network
            if (item.toString().startsWith("192.168"))
            {
                continue;
            }

            // Should get 183.172.xxx.xxx (Tsinghua Univ)
            return item.toString();
        }
    }

    return QHostAddress(QHostAddress::LocalHost).toString();
}


void Client::HandleMessage(const QString& message)
{
}


void Client::Unregister()
{
    auto localHost = GetLocalAddress();
    auto port      = ClientServer->serverPort();

    auto message = "UNREGISTER|" + localHost + "|" + QString::number(port);
    SendMessage(message);

    ClientServer->close();
}
