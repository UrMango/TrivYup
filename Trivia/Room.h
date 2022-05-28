#pragma once
#include <string>
#include "Helper.h"
#include <vector>
#include "LoggedUser.h"

class Room
{
public:
	Room(const LoggedUser user,const RoomData roomData);
	void addUser(LoggedUser user);
	void removeUser(LoggedUser user);
	std::vector<string> getAllUsers();
	unsigned int getRoomState()const;
private:
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;
};
