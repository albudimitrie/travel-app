#ifndef PHOTOATTRACTIONREQUEST_H
#define PHOTOATTRACTIONREQUEST_H

#include "irequest.h"

class PhotoAttractionRequest : public IRequest
{
private:
    int id;
public:
    PhotoAttractionRequest(int id);
    QByteArray getRequest()override;
};

#endif // PHOTOATTRACTIONREQUEST_H
