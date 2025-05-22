#pragma once
#include "iRepository.h"

class User;

class UserRepository :  public ARepository<User>
{
	void updateWalletForUser(const std::string& username, double new_balance);
	void createWalletForUser(const std::string& username);
public:
	//--------INHERITED--------------------------
	virtual void create(const User& obj) override;
	virtual void update(const User& obj) override;
	virtual void remove(const User& obj)override;
	virtual std::vector<User*> getAll()override;
	virtual ~UserRepository() = default;


	//-------CONCRETE----------------------------
	bool userExists(const std::string& username, const std::string& password);
	bool isAdmin(const std::string& username, const std::string& password);
	bool isUsernameTaken(const std::string& username);
	int getIDForUsername(const std::string& username);
	double getFundsForUser(const std::string& username);

	void addNewSearch(const std::string& username, const std::string& content);
	std::vector<std::string> getLatestSearches(const std::string& username);




};

