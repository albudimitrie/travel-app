#pragma once

class User;

class CurrentUser
{
	static CurrentUser* instance;

	User* _current;
	CurrentUser() = default;
	CurrentUser(const CurrentUser& obj) = delete;
	CurrentUser(CurrentUser&& obj) = delete;
	~CurrentUser() = default;

public:
	static CurrentUser* getInstance();
	static void destroyInstance();
	void setActive(User* user);
	void disconnect();
	User* getUser() const { return _current; }
	bool isLogged() { return _current != nullptr; }


};

