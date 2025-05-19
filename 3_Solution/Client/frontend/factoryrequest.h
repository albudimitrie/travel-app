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
#include"allattractionsrequest.h"
#include"photoattractionrequest.h"
#include"allroutesrequest.h"
#include"phototransportationrequest.h"
#include"tripsrequest.h"

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
    static IRequest* allattractionsReq();
    static IRequest* photoattractionReq(int id);
    static IRequest* allroutesReq();
    static IRequest* phototransportationReq(int id);
    static IRequest* tripsReq(QString username);

};

#endif // FACTORYREQUEST_H
