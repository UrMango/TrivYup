#pragma once
#include <string>
#include "Helper.h"
#include <vector>
#include "LoggedUser.h"

class Room
{

public:
	void addUser(LoggedUser);
	void removeUser(LoggedUser);
	std::vector<string> getAllUsers();
private:
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;
};
