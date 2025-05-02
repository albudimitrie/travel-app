#ifndef ACCOMMODATIONREQUEST_H
#define ACCOMMODATIONREQUEST_H

#include "irequest.h"

class AccommodationRequest : public IRequest
{
private:
    int id;
public:
    AccommodationRequest(int id);
    QByteArray getRequest()override;
};

#endif // ACCOMMODATIONREQUEST_H
