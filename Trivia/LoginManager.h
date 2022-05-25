#pragma once

#include <iostream>

class LoginManager
{
public:
	void signup(std::string username, std::string password, std::string email);
	void login(std::string username, std::string password);
	void logout(std::string username);

};

