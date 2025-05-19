#include "allattractionsrequest.h"

AllAttractionsRequest::AllAttractionsRequest() {}

QByteArray AllAttractionsRequest::getRequest()
{
    QJsonObject jsonObj;
    jsonObj["action"]="GET_ALL_ATTRACTIONS";

    QJsonDocument jsonDoc(jsonObj);

    QByteArray jsonData = jsonDoc.toJson();

    return jsonData;
}

