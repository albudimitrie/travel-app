#ifndef LOGINREQUEST_H
#define LOGINREQUEST_H

#include "irequest.h"

class LoginRequest : public IRequest
{
private:
    QString username="";
    QString password="";
public:
    LoginRequest(QString username,QString password);
    QByteArray getRequest()override;

};

#endif // LOGINREQUEST_H
