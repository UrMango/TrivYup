#pragma once

#include <iostream>

class LoggedUser
{
private:
	std::string m_username;
public:
	LoggedUser(std::string username) : m_username(username) {};
	~LoggedUser() {};

	std::string getUsername();

};

