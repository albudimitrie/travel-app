#ifndef LOGOUTREQUEST_H
#define LOGOUTREQUEST_H

#include "irequest.h"

class LogoutRequest : public IRequest
{
private:
    QString username="";
public:
    LogoutRequest(QString username);
    QByteArray getRequest()override;
};

#endif // LOGOUTREQUEST_H
