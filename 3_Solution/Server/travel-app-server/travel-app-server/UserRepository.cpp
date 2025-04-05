#include "UserRepository.h"
#include "User.h"

void UserRepository::create(const User& obj)
{
	std::string query = "INSERT INTO Users(username, password) VALUES ('" + obj.getUsername() + "','" + obj.getPassword() + "');";
	SQLHSTMT stmt;
	SQLRETURN ret;

	ret = SQLAllocHandle(SQL_HANDLE_STMT, _db->getDBC(), &stmt);

	ret = SQLExecDirectA(stmt, (SQLCHAR*)query.c_str(), SQL_NTS);

	if (!SQL_SUCCEEDED(ret)) {
		SQLFreeHandle(SQL_HANDLE_STMT, stmt);
		throw 1;
		Logger::getInstance()->logDBActions(LogStatus::ERROR_, "Insert into table Users failed");
	}

	Logger::getInstance()->logDBActions(LogStatus::SUCCES, "Insert into table Users succeded");

}

void UserRepository::update(const User& obj)
{


}

void UserRepository::remove(const User& obj)
{
	//TODO
}

std::vector<User*> UserRepository::getAll()
{
	//TODO
	return std::vector<User*>();
}

std::vector<User*> UserRepository::getByFilters(std::vector<Filter *>)
{
	return std::vector<User*>();
}

bool UserRepository::userExists(const std::string& username, const std::string& password)
{
	std::string query = "SELECT ID FROM Users WHERE username='" + username + "' and password ='" + password + "';";
	SQLHSTMT stmt;
	SQLRETURN ret;

	ret = SQLAllocHandle(SQL_HANDLE_STMT, _db->getDBC(), &stmt);
	if (!SQL_SUCCEEDED(ret))
	{
		throw 1;
	}

	ret = SQLExecDirectA(stmt, (SQLCHAR *)query.c_str(), SQL_NTS);

	if (!SQL_SUCCEEDED(ret)) {
		SQLFreeHandle(SQL_HANDLE_STMT, stmt);
		throw 1;
	}

	bool res;
	if (SQLFetch(stmt) == SQL_SUCCESS) {res = true;}
	else{res =  false;}

	SQLFreeHandle(SQL_HANDLE_STMT, stmt);
	return res;
}

bool UserRepository::isAdmin(const std::string& username, const std::string& password)
{
	std::string query = "SELECT ID FROM Users WHERE username='" + username + "' and password ='" + password + "' AND isAdmin = 1;";
	SQLHSTMT stmt;
	SQLRETURN ret;

	ret = SQLAllocHandle(SQL_HANDLE_STMT, _db->getDBC(), &stmt);
	if (!SQL_SUCCEEDED(ret))
	{
		throw 1;
	}

	ret = SQLExecDirectA(stmt, (SQLCHAR*)query.c_str(), SQL_NTS);

	if (!SQL_SUCCEEDED(ret)) {
		SQLFreeHandle(SQL_HANDLE_STMT, stmt);
		throw 1;
	}

	bool res;
	if (SQLFetch(stmt) == SQL_SUCCESS) { res = true; }
	else { res = false; }

	SQLFreeHandle(SQL_HANDLE_STMT, stmt);
	return res;
}

bool UserRepository::isUsernameTaken(const std::string& username)
{
	std::string query = "SELECT ID FROM Users WHERE username='" + username + "';";
	SQLHSTMT stmt;
	SQLRETURN ret;

	ret = SQLAllocHandle(SQL_HANDLE_STMT, _db->getDBC(), &stmt);
	if (!SQL_SUCCEEDED(ret))
	{
		throw 1;
	}

	ret = SQLExecDirectA(stmt, (SQLCHAR*)query.c_str(), SQL_NTS);

	if (!SQL_SUCCEEDED(ret)) {
		SQLFreeHandle(SQL_HANDLE_STMT, stmt);
		throw 1;
	}

	bool res;
	if (SQLFetch(stmt) == SQL_SUCCESS) { res = true; }
	else { res = false; }

	SQLFreeHandle(SQL_HANDLE_STMT, stmt);
	return res;
}

void UserRepository::addNewSearch(const std::string& username, const std::string& content)
{
	std::string query = "INSERT INTO SearchHistory(username, content) VALUES ( '" + username +"' , '" +content +"'" + ");";

	SQLHSTMT stmt;
	SQLRETURN ret;

	ret = SQLAllocHandle(SQL_HANDLE_STMT, _db->getDBC(), &stmt);

	ret = SQLExecDirectA(stmt, (SQLCHAR*)query.c_str(), SQL_NTS);

	if (!SQL_SUCCEEDED(ret)) {
		SQLFreeHandle(SQL_HANDLE_STMT, stmt);
		throw 1;
		Logger::getInstance()->logDBActions(LogStatus::ERROR_, "Insert into table SearchHistory failed");
	}

	Logger::getInstance()->logDBActions(LogStatus::SUCCES, "Insert into table SearchHistory succeded");
}

std::vector<std::string> UserRepository::getLatestSearches(const std::string& username)
{
	std::vector<std::string> results;
	std::string query = "SELECT TOP(10) content FROM SearchHistory WHERE username='" + username + "' ORDER BY id DESC;";

	SQLHSTMT stmt;
	SQLRETURN ret;

	ret = SQLAllocHandle(SQL_HANDLE_STMT, _db->getDBC(), &stmt);
	if (!SQL_SUCCEEDED(ret)) {
		throw 1;
	}

	ret = SQLExecDirectA(stmt, (SQLCHAR*)query.c_str(), SQL_NTS);
	if (!SQL_SUCCEEDED(ret)) {
		SQLFreeHandle(SQL_HANDLE_STMT, stmt);
		throw 1;
	}

	char content[1024];
	SQLLEN contentInd;

	ret = SQLBindCol(stmt, 1, SQL_C_CHAR, content, sizeof(content), &contentInd);
	if (!SQL_SUCCEEDED(ret)) {
		SQLFreeHandle(SQL_HANDLE_STMT, stmt);
		throw 1;
	}

	while (SQLFetch(stmt) == SQL_SUCCESS) {
		results.emplace_back(content);
	}

	SQLFreeHandle(SQL_HANDLE_STMT, stmt);

	return results;
}