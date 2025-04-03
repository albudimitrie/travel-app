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
	}



}

void UserRepository::update(const User& obj)
{


}

void UserRepository::remove(const User& obj)
{
}

std::vector<User*> UserRepository::getAll()
{
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
	return true;
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
