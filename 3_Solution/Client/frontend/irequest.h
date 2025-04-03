#ifndef IREQUEST_H
#define IREQUEST_H
#include<QString>
#include <QJsonDocument>
#include <QJsonObject>

class IRequest
{
public:
   virtual QByteArray getRequest() = 0;
};

#endif // IREQUEST_H
