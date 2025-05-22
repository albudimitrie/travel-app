#include "logoutrequest.h"


LogoutRequest::LogoutRequest(QString username,double balance)
{
    this->username=username;
    this->balance=balance;
}

QByteArray LogoutRequest::getRequest()
{
    QJsonObject jsonObj;
    jsonObj["action"]="LOG_OUT";
    jsonObj["username"] = username;
    jsonObj["balance"]=balance;

    QJsonDocument jsonDoc(jsonObj);

    QByteArray jsonData = jsonDoc.toJson();

    return jsonData;
}
