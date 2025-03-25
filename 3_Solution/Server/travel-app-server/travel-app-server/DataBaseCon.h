#pragma once

#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <string>
#include <vector>



class DataBaseCon
{
	SQLHENV _hEnv;
	SQLHDBC _hDbc;
	bool _connected;



	static DataBaseCon* _instance;
	DataBaseCon();
	~DataBaseCon();
	DataBaseCon(const DataBaseCon& obj) = delete;
	DataBaseCon(DataBaseCon&& obj) = delete;


public:
	static DataBaseCon* getInstance();
	static void destroyInstance();

	SQLHENV getEnv() const { return _hEnv; }
	SQLHDBC getDBC()const { return _hDbc;  }
	
	bool connect(const std::string& serverName, const std::string& dbName);
	void disconnect();
	bool isConnected() const;
	bool executeQuery(std::string query, std::vector<std::vector<std::string>>& result);
	bool insert(std::string query, std::vector<std::vector<std::string>>& toInsert);
};

