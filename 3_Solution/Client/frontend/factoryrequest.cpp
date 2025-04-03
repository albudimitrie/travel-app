#include "factoryrequest.h"

IRequest* FactoryRequest::loginReq(QString username,QString password)
{
    return new LoginRequest(username,password);
}

IRequest* FactoryRequest::registerReq(QString username,QString password)
{
    return new RegisterRequest(username,password);
}
