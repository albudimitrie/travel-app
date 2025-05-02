#ifndef NUMBERACCOMMODATIONSREQUEST_H
#define NUMBERACCOMMODATIONSREQUEST_H

#include "irequest.h"

class NumberAccommodationsRequest : public IRequest
{
public:
    NumberAccommodationsRequest();
    QByteArray getRequest()override;
};

#endif // NUMBERACCOMMODATIONSREQUEST_H
