#ifndef ALLROUTESREQUEST_H
#define ALLROUTESREQUEST_H

#include "irequest.h"

class AllRoutesRequest : public IRequest
{
public:
    AllRoutesRequest();
    QByteArray getRequest()override;
};

#endif // ALLROUTESREQUEST_H
