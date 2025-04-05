#ifndef FACTORYREQUEST_H
#define FACTORYREQUEST_H

#include"loginrequest.h"
#include"registerrequest.h"
#include"logoutrequest.h"

class FactoryRequest
{
public:
    static IRequest* loginReq(QString username,QString password);
    static IRequest* registerReq(QString username,QString password);
    static IRequest* logoutReq(QString username);
};

#endif // FACTORYREQUEST_H
