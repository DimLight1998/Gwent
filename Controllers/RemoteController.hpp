//
// Created on 2017/09/09 at 22:39.
//

#ifndef GWENT_REMOTECONTROLLER_HPP
#define GWENT_REMOTECONTROLLER_HPP

#include "Network/Server.hpp"


class RemoteController : public Server
{
Q_OBJECT
protected:
    void HandleMessage(const QString& message) override;

    void ResetServerData();
    int PlayerCounter = 0;
};


#endif //GWENT_REMOTECONTROLLER_HPP
