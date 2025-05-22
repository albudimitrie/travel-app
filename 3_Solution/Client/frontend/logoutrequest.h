#ifndef LOGOUTREQUEST_H
#define LOGOUTREQUEST_H

#include "irequest.h"

class LogoutRequest : public IRequest
{
private:
    QString username="";
    double balance=0;
public:
    LogoutRequest(QString username,double balance);
    QByteArray getRequest()override;
};

#endif // LOGOUTREQUEST_H
