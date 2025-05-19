#ifndef TRIPSREQUEST_H
#define TRIPSREQUEST_H

#include "irequest.h"

class TripsRequest : public IRequest
{
private:
    QString username="";
public:
    TripsRequest(QString username);
    QByteArray getRequest()override;
};

#endif // TRIPSREQUEST_H
