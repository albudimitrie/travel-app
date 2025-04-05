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

bool DataBaseCon::executeQuery(std::string query, std::vector<std::vector<std::string>>& result)
{
    if (!_connected) {
        std::cerr << "Not connected to the database!" << std::endl;
        return false; 
    }

    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, _hDbc, &hStmt);

    //conversie
    int len = MultiByteToWideChar(CP_ACP, 0, query.c_str(), -1, NULL, 0);
    SQLWCHAR* wQuery = new SQLWCHAR[len];
    MultiByteToWideChar(CP_ACP, 0, query.c_str(), -1, wQuery, len);

    SQLRETURN ret = SQLExecDirectW(hStmt, wQuery, SQL_NTS);
    delete[] wQuery;

    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        SQLWCHAR sqlState[6], message[SQL_MAX_MESSAGE_LENGTH];
        SQLINTEGER nativeError;
        SQLSMALLINT length;

        SQLGetDiagRec(SQL_HANDLE_STMT, hStmt, 1, sqlState, &nativeError,
            message, sizeof(message), &length);

        std::cerr << L"Eroare executie SQL: " << sqlState
            <<" (cod " << nativeError <<"): " << message << std::endl;



        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        return false;
    }

    SQLSMALLINT numColumns;
    SQLNumResultCols(hStmt, &numColumns);

    while ((ret = SQLFetch(hStmt)) != SQL_NO_DATA) {
        std::vector<std::string> row;
        for (SQLSMALLINT i = 1; i <= numColumns; i++) {
            SQLCHAR buffer[256];
            SQLLEN indicator;
            SQLGetData(hStmt, i, SQL_C_CHAR, buffer, sizeof(buffer), &indicator);
            if (indicator != SQL_NULL_DATA) {
                row.push_back((char*)buffer);
            }
            else {
                row.push_back("");
            }
        }
        result.push_back(std::move(row));
    }

    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    return true;
}

bool DataBaseCon::insert(std::string query, std::vector<std::vector<std::string>>& toInsert)
{
    if (!_connected) {
        std::cerr << "Not connected to the database!" << std::endl;
        return false;
    }

    bool allSuccessful = true;

    for (const auto& row : toInsert) {
        std::string finalQuery = query;

        for (const auto& value : row) {
            size_t pos = finalQuery.find("?");
            if (pos != std::string::npos) {
                std::string escapedValue = value;
                size_t valuePos = 0;
                while ((valuePos = escapedValue.find("'", valuePos)) != std::string::npos) {
                    escapedValue.replace(valuePos, 1, "''");
                    valuePos += 2;
                }
                finalQuery.replace(pos, 1, "'" + escapedValue + "'");
            }
        }

        SQLHSTMT hStmt;
        SQLAllocHandle(SQL_HANDLE_STMT, _hDbc, &hStmt);

        int len = MultiByteToWideChar(CP_ACP, 0, finalQuery.c_str(), -1, NULL, 0);
        SQLWCHAR* wFinalQuery = new SQLWCHAR[len];
        MultiByteToWideChar(CP_ACP, 0, finalQuery.c_str(), -1, wFinalQuery, len);

        SQLRETURN ret = SQLExecDirectW(hStmt, wFinalQuery, SQL_NTS);
        delete[] wFinalQuery;

        if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
            SQLWCHAR sqlState[6], message[SQL_MAX_MESSAGE_LENGTH];
            SQLINTEGER nativeError;
            SQLSMALLINT length;

            SQLGetDiagRec(SQL_HANDLE_STMT, hStmt, 1, sqlState, &nativeError,
                message, sizeof(message), &length);

            std::wcerr << L"Eroare executie SQL: " << sqlState
                << L" (cod " << nativeError << L"): " << message << std::endl;
            std::cerr << "Query: " << finalQuery << std::endl;

            allSuccessful = false;
        }

        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    }

    return allSuccessful;
  
}
