#ifndef IREQUEST_H
#define IREQUEST_H
#include<QString>

class IRequest
{
public:
   virtual QByteArray getRequest() = 0;
};

#endif // IREQUEST_H
