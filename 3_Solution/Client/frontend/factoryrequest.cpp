#include "factoryrequest.h"

IRequest* FactoryRequest::loginReq(QString username,QString password)
{
    return new LoginRequest(username,password);
}

IRequest* FactoryRequest::registerReq(QString username,QString password)
{
    return new RegisterRequest(username,password);
}

IRequest* FactoryRequest::logoutReq(QString username,double balance)
{
    return new LogoutRequest(username,balance);
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

IRequest* FactoryRequest::allattractionsReq()
{
    return new AllAttractionsRequest();
}

IRequest* FactoryRequest::photoattractionReq(int id)
{
    return new PhotoAttractionRequest(id);
}

IRequest* FactoryRequest::allroutesReq()
{
    return new AllRoutesRequest();
}

IRequest* FactoryRequest::phototransportationReq(int id)
{
    return new PhotoTransportationRequest(id);
}

IRequest* FactoryRequest::tripsReq(QString username)
{
    return new TripsRequest(username);
}
