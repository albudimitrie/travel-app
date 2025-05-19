#include "DataBaseCon.h"
#include <iostream>
#include "Logger.h"

DataBaseCon* DataBaseCon::_instance = nullptr;

DataBaseCon::DataBaseCon()
    :_hEnv{SQL_NULL_HENV}, _hDbc{SQL_NULL_HDBC}, _connected{false}
{
    SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &_hEnv);
    SQLSetEnvAttr(_hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);
}

DataBaseCon::~DataBaseCon()
{
}

DataBaseCon* DataBaseCon::getInstance()
{
    if (!_instance)
    {
        _instance = new DataBaseCon();

    }
    return _instance;
}

void DataBaseCon::destroyInstance()
{
    if (_instance)
    {
        delete _instance;
        _instance = nullptr;
    }
}

bool DataBaseCon::connect(const std::string& serverName, const std::string& dbName)
{
    std::string connStr = "DRIVER={SQL Server};SERVER=" + serverName + ";DATABASE=" + dbName + ";Trusted_Connection=yes;";
    SQLAllocHandle(SQL_HANDLE_DBC, _hEnv, &_hDbc);

    SQLWCHAR outConnStr[1024];
    SQLSMALLINT outConnStrLen;

    int len = MultiByteToWideChar(CP_ACP, 0, connStr.c_str(), -1, NULL, 0);
    SQLWCHAR* wConnStr = new SQLWCHAR[len];
    MultiByteToWideChar(CP_ACP, 0, connStr.c_str(), -1, wConnStr, len);

    SQLRETURN ret = SQLDriverConnectW(_hDbc, NULL, wConnStr, SQL_NTS,
        outConnStr, sizeof(outConnStr), &outConnStrLen,
        SQL_DRIVER_NOPROMPT);

    delete[] wConnStr;

    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        _connected = true;
        return true;
    }
    else {
        SQLWCHAR sqlState[6], message[SQL_MAX_MESSAGE_LENGTH];
        SQLINTEGER nativeError;
        SQLSMALLINT length;

        SQLGetDiagRec(SQL_HANDLE_DBC, _hDbc, 1, sqlState, &nativeError,
            message, sizeof(message), &length);

        std::wcerr << L"Eroare conectare SQL: " << sqlState
            << L" (cod " << nativeError << L"): " << message << std::endl;
        
        Logger::getInstance()->logDBActions(LogStatus::ERROR_, "Eroare conectare SQL");

        return false;
    }
}

void DataBaseCon::disconnect()
{
    if (!_connected)
    {
        return;
    }
    SQLDisconnect(_hDbc);
    SQLFreeHandle(SQL_HANDLE_DBC, _hDbc);
    _connected = false;

}

bool DataBaseCon::isConnected() const
{
    return _connected;
}
