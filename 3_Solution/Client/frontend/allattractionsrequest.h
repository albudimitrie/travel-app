#ifndef ALLATTRACTIONSREQUEST_H
#define ALLATTRACTIONSREQUEST_H

#include "irequest.h"

class AllAttractionsRequest : public IRequest
{
public:
    AllAttractionsRequest();
    QByteArray getRequest()override;
};

#endif // ALLATTRACTIONSREQUEST_H
