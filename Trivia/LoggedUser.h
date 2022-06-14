#pragma once

#include <iostream>
#include "Room.h"
class Room;
struct RoomData;
class LoggedUser
{
private:
	std::string m_username;
	Room* roomOfOser;
public:
	LoggedUser(std::string username) : m_username(username){};
	~LoggedUser() {};

	std::string getUsername();
	Room* getRoom()const;
	void changeRoom(Room* Room);
	void removeRoom();


};

