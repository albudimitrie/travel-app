#include "ack.h"

ACK::ACK() {}

QByteArray ACK::getRequest()
{
    QJsonObject jsonObj;
    jsonObj["action"]="ACK";

    QJsonDocument jsonDoc(jsonObj);

    QByteArray jsonData = jsonDoc.toJson();

    return jsonData;
}
