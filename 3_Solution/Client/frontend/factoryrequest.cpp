#include "factoryrequest.h"

IRequest* FactoryRequest::loginReq(QString username,QString password)
{
    return new LoginRequest(username,password);
}

IRequest* FactoryRequest::registerReq(QString username,QString password)
{
    return new RegisterRequest(username,password);
}

IRequest* FactoryRequest::logoutReq(QString username)
{
    return new LogoutRequest(username);
}

IRequest* FactoryRequest::historyReq(QString username)
{
    return new HistoryRequest(username);
}
