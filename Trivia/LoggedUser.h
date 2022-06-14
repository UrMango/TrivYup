#pragma once

#include <iostream>

class LoggedUser
{
private:
	std::string m_username;
	int roodIdOfOser;
public:
	LoggedUser(std::string username) : m_username(username) {};
	~LoggedUser() {};

	std::string getUsername();
	int getRoomId()const;
	void changeRoomId(const int newId);

};

