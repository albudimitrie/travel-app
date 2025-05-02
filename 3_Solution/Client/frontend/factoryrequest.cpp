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

IRequest* FactoryRequest::accomodationReq(int id)
{
    return new AccommodationRequest(id);
}

IRequest* FactoryRequest::numberaccommodationsReq()
{
    return new NumberAccommodationsRequest();
}

IRequest* FactoryRequest::photoaccomodationReq(int id)
{
    return new PhotoAccommodationRequest(id);
}

IRequest* FactoryRequest::ackReq()
{
    return new ACK();
}
