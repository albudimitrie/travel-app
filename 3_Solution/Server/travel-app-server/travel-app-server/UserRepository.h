#pragma once
#include "iRepository.h"

class User;

class UserRepository :  public ARepository<User>
{

public:
	//--------INHERITED--------------------------
	virtual void create(const User& obj) override;
	virtual void update(const User& obj) override;
	virtual void remove(const User& obj)override;
	virtual std::vector<User*> getAll()override;
	virtual std::vector<User*> getByFilters(std::vector<Filter *>) override;
	virtual ~UserRepository() = default;


	//-------CONCRETE----------------------------

	bool userExists(const std::string& username, const std::string& password);
	bool isAdmin(const std::string& username, const std::string& password);
	bool isUsernameTaken(const std::string& username);




};

