#ifndef FACTORYREQUEST_H
#define FACTORYREQUEST_H

#include"loginrequest.h"
#include"registerrequest.h"
#include"logoutrequest.h"
#include"historyrequest.h"
#include"accommodationrequest.h"
#include"numberaccommodationsrequest.h"
#include"photoaccommodationrequest.h"
#include"ack.h"

class FactoryRequest
{
public:
    static IRequest* loginReq(QString username,QString password);
    static IRequest* registerReq(QString username,QString password);
    static IRequest* logoutReq(QString username);
    static IRequest* historyReq(QString username);
    static IRequest* accomodationReq(int id);
    static IRequest* numberaccommodationsReq();
    static IRequest* photoaccomodationReq(int id);
    static IRequest* ackReq();

};

#endif // FACTORYREQUEST_H
