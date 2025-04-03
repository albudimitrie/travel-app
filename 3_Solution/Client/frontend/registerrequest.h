#ifndef REGISTERREQUEST_H
#define REGISTERREQUEST_H

#include "irequest.h"

class RegisterRequest : public IRequest
{
private:
    QString username="";
    QString password="";
public:
    RegisterRequest(QString username,QString password);
    QByteArray getRequest()override;
};

#endif // REGISTERREQUEST_H
