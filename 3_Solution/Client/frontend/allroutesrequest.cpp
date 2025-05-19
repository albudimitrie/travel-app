#include "allroutesrequest.h"

AllRoutesRequest::AllRoutesRequest() {}

QByteArray AllRoutesRequest::getRequest()
{
    QJsonObject jsonObj;
    jsonObj["action"]="GET_ALL_ROUTES";

    QJsonDocument jsonDoc(jsonObj);

    QByteArray jsonData = jsonDoc.toJson();

    return jsonData;
}
