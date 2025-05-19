#include "tripsrequest.h"

TripsRequest::TripsRequest(QString username)
{
    this->username=username;
}

QByteArray TripsRequest::getRequest()
{
    QJsonObject jsonObj;
    jsonObj["action"]="GET_TRIP_HISTORY";
    jsonObj["username"] = username;

    QJsonDocument jsonDoc(jsonObj);

    QByteArray jsonData = jsonDoc.toJson();

    return jsonData;
}
