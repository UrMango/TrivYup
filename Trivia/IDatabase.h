#pragma once

#include <iostream>
#include "sqlite3.h"

class IDatabase
{
public:
	IDatabase();
	~IDatabase();

	bool doesUserExist(std::string username);
	bool doesPasswordMatch(std::string username, std::string pword);
	void addNewUser(std::string username, std::string pword, std::string email);
private:
	sqlite3* db;
	char* errMessage;
};

