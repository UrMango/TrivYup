#pragma once

#include <iostream>
#include "sqlite3.h"

class IDatabase
{
public:
	virtual bool doesUserExist(std::string username) = 0;
	virtual bool doesPasswordMatch(std::string username, std::string pword) = 0;
	virtual void addNewUser(std::string username, std::string pword, std::string email) = 0;
};

