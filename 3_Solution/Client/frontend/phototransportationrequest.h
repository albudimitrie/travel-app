#ifndef PHOTOTRANSPORTATIONREQUEST_H
#define PHOTOTRANSPORTATIONREQUEST_H

#include "irequest.h"

class PhotoTransportationRequest : public IRequest
{
private:
    int id;
public:
    PhotoTransportationRequest(int id);
    QByteArray getRequest()override;
};

#endif // PHOTOTRANSPORTATIONREQUEST_H
