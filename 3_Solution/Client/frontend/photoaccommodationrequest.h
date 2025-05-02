#ifndef PHOTOACCOMMODATIONREQUEST_H
#define PHOTOACCOMMODATIONREQUEST_H

#include "irequest.h"

class PhotoAccommodationRequest : public IRequest
{
private:
    int id;
public:
    PhotoAccommodationRequest(int id);
     QByteArray getRequest()override;
};

#endif // PHOTOACCOMMODATIONREQUEST_H
