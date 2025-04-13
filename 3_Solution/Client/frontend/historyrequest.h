#ifndef HISTORYREQUEST_H
#define HISTORYREQUEST_H

#include "irequest.h"

class HistoryRequest : public IRequest
{
private:
    QString username="";
public:
    HistoryRequest(QString username);
    QByteArray getRequest()override;
};

#endif // HISTORYREQUEST_H
