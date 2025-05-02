#ifndef ACK_H
#define ACK_H

#include "irequest.h"

class ACK : public IRequest
{
public:
    ACK();
    QByteArray getRequest()override;
};

#endif // ACK_H
