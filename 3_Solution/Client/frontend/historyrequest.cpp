#include "historyrequest.h"

HistoryRequest::HistoryRequest(QString username)
{
    this->username=username;
}

QByteArray HistoryRequest::getRequest()
{
    QJsonObject jsonObj;
    jsonObj["action"]="GET_SEARCH_HISTORY";
    jsonObj["username"] = username;

    QJsonDocument jsonDoc(jsonObj);

    QByteArray jsonData = jsonDoc.toJson();

    return jsonData;
}
