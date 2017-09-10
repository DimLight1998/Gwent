//
// Created on 2017/09/10 at 14:28.
//

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtCore/QTimer>
#include <QtCore/QEventLoop>
#include "RandomInteger.hpp"


int RandomInteger::GetRandomInteger(int min, int max)
{
    QString base = "https://www.random.org/integers/?num=1&min=%1&max=%2&col=1&base=10&format=plain&rnd=new";
    QString url  = base.arg(min).arg(max);

    QNetworkRequest request;

    auto networkAccessManager = new QNetworkAccessManager();

    request.setUrl(QUrl(url));
    networkAccessManager->get(request);

    QEventLoop eventLoop;

    int randomNumber = 1;

    QObject::connect(
        networkAccessManager, &QNetworkAccessManager::finished,
        [&randomNumber, &eventLoop, networkAccessManager, max, min](QNetworkReply *reply)
        {
          randomNumber = QString(reply->readAll()).split('\n')[0].toInt();

          // if there is error, use local random generator
          if (reply->error() != QNetworkReply::NoError)
          {
              qsrand(static_cast<uint>(QDateTime::currentMSecsSinceEpoch()));
              randomNumber = qrand();
              randomNumber = randomNumber % (max - min + 1) + min;
          }

          networkAccessManager->deleteLater();
          eventLoop.exit(0);
        });

    eventLoop.exec();

    return randomNumber;
}


int RandomInteger::GetRandomInteger()
{
    return GetRandomInteger(-100000000, 100000000);
}
