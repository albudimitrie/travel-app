#ifndef FACTORYREQUEST_H
#define FACTORYREQUEST_H

#include"loginrequest.h"

class FactoryRequest
{
public:
    static IRequest* loginReq(QString username,QString password);
};

#endif // FACTORYREQUEST_H
