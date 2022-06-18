#pragma once

#include <iostream>
#include <vector>
#include "SqliteDataBase.h"
#include "LoggedUser.h"

class LoginManager
{
private:
	IDatabase* m_database;
	std::vector<LoggedUser> m_loggedUsers;
public:
	LoginManager(IDatabase* database) : m_database(database) {};
	~LoginManager() {};

	bool signup(std::string username, std::string password, std::string email);
	bool login(std::string username, std::string password);
	void logout(std::string username);

};

