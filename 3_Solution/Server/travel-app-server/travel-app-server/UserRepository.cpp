#include "UserRepository.h"
#include "User.h"

void UserRepository::updateWalletForUser(const std::string& username, double new_balance)
{
	std::string balance = std::to_string(new_balance);
	std::string query = "UPDATE Wallet SET balance=" + balance + " WHERE username='" + username + "';";
	SQLHSTMT stmt;
	SQLRETURN ret;

	ret = SQLAllocHandle(SQL_HANDLE_STMT, _db->getDBC(), &stmt);

	ret = SQLExecDirectA(stmt, (SQLCHAR*)query.c_str(), SQL_NTS);

	if (!SQL_SUCCEEDED(ret)) {
		SQLFreeHandle(SQL_HANDLE_STMT, stmt);
		throw std::runtime_error{ "Nu s a putut executa query updateWallet" };
		Logger::getInstance()->logDBActions(LogStatus::ERROR_, "Updated wallet for user" + username + " failed");
	}

	Logger::getInstance()->logDBActions(LogStatus::SUCCES, "Updated wallet for user " + username + " succedeed");
}

void UserRepository::createWalletForUser(const std::string& username)
{
	std::string query = "INSERT INTO Wallet(username, balance) VALUES ('" + username + "', 0)";
	SQLHSTMT stmt;
	SQLRETURN ret;

	ret = SQLAllocHandle(SQL_HANDLE_STMT, _db->getDBC(), &stmt);

	ret = SQLExecDirectA(stmt, (SQLCHAR*)query.c_str(), SQL_NTS);

	if (!SQL_SUCCEEDED(ret)) {
		SQLFreeHandle(SQL_HANDLE_STMT, stmt);
		throw std::runtime_error{ "Nu s a putut crea portofel pentru user" };
		Logger::getInstance()->logDBActions(LogStatus::ERROR_, "Creating wallet for user " + username + " failed");
	}

	Logger::getInstance()->logDBActions(LogStatus::SUCCES, "Creating wallet for user " + username + " succedeed");
}

void UserRepository::create(const User& obj)
{
	std::string query = "INSERT INTO Users(username, password) VALUES ('" + obj.getUsername() + "', '" + obj.getPassword() + "' ) ;";
	SQLHSTMT stmt;
	SQLRETURN ret;

	ret = SQLAllocHandle(SQL_HANDLE_STMT, _db->getDBC(), &stmt);

	ret = SQLExecDirectA(stmt, (SQLCHAR*)query.c_str(), SQL_NTS);

	if (!SQL_SUCCEEDED(ret)) {
		SQLFreeHandle(SQL_HANDLE_STMT, stmt);
		throw std::runtime_error{ "Nu s a putut crea userul" };
		Logger::getInstance()->logDBActions(LogStatus::ERROR_, "Insert into table Users failed");
	}

	Logger::getInstance()->logDBActions(LogStatus::SUCCES, "Insert into table Users succeded");
	createWalletForUser(obj.getUsername());

}

void UserRepository::update(const User& obj)
{
	updateWalletForUser(obj.getUsername(), obj.getBalance());
}

void UserRepository::remove(const User& obj)
{
	throw std::runtime_error{ "Aceasta functie nu a fost implementata\n" };
}

std::vector<User*> UserRepository::getAll()
{
	throw std::runtime_error{ "Aceasta functie nu a fost implementata\n" };
}

bool UserRepository::userExists(const std::string& username, const std::string& password)
{
	std::string query = "SELECT ID FROM Users WHERE username='" + username + "' and password ='" + password + "';";
	SQLHSTMT stmt;
	SQLRETURN ret;

	ret = SQLAllocHandle(SQL_HANDLE_STMT, _db->getDBC(), &stmt);
	if (!SQL_SUCCEEDED(ret))
	{
		throw std::runtime_error{ "Nu s a putut aloca handler pentru query userExists" };
	}

	ret = SQLExecDirectA(stmt, (SQLCHAR *)query.c_str(), SQL_NTS);

	if (!SQL_SUCCEEDED(ret)) {
		SQLFreeHandle(SQL_HANDLE_STMT, stmt);
		throw std::runtime_error{ "Nu s a putut executa query userExists" };
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
		throw std::runtime_error{"Nu s a putut executa query isAdmin"};
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

int UserRepository::getIDForUsername(const std::string& username)
{
	std::string query = "SELECT ID FROM Users WHERE username = '" + username + "'";

	SQLHSTMT stmt;
	SQLRETURN ret;

	ret = SQLAllocHandle(SQL_HANDLE_STMT, _db->getDBC(), &stmt);
	if (!SQL_SUCCEEDED(ret)) {
		throw std::runtime_error("Eroare handler pentru statement getAllAccommodations");
	}

	ret = SQLExecDirectA(stmt, (SQLCHAR*)query.c_str(), SQL_NTS);
	if (!SQL_SUCCEEDED(ret)) {
		SQLFreeHandle(SQL_HANDLE_STMT, stmt);
		throw std::runtime_error("Eroare executare query destinatii");
	}
	SQLINTEGER ID;
	SQLBindCol(stmt, 1, SQL_C_LONG, &ID, 0, NULL);
	if (SQLFetch(stmt) == SQL_SUCCESS)
	{
		return ID;
	}
	else
	{
		throw std::runtime_error{ "Nu exista acest user in baza de date\n" };
	}
}

double UserRepository::getFundsForUser(const std::string& username)
{
	std::string query = "SELECT balance FROM Wallet WHERE username = '" + username + "';";
	SQLHSTMT stmt;
	SQLRETURN ret;

	ret = SQLAllocHandle(SQL_HANDLE_STMT, _db->getDBC(), &stmt);
	if (!SQL_SUCCEEDED(ret)) {
		throw std::runtime_error("Eroare handler pentru statement getFundsForUser");
	}

	ret = SQLExecDirectA(stmt, (SQLCHAR*)query.c_str(), SQL_NTS);
	if (!SQL_SUCCEEDED(ret)) {
		SQLFreeHandle(SQL_HANDLE_STMT, stmt);
		throw std::runtime_error("Eroare executare query wallet for user");
	}
	SQLDOUBLE funds;
	SQLBindCol(stmt, 1, SQL_C_DOUBLE, &funds, 0, NULL);
	if (SQLFetch(stmt) == SQL_SUCCESS)
	{
		Logger::getInstance()->logDBActions(LogStatus::SUCCES, "Got funds for user " + username);
		return funds;
	}
	else
	{
		throw std::runtime_error{ "Nu exista portofel pentru acest user\n" };
		Logger::getInstance()->logDBActions(LogStatus::ERROR_, "Couldnt get funds for user " + username);
	}

	return 0.0;
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