#pragma once

#include <iostream>
#include "Room.h"
class Room;
struct RoomData;
class LoggedUser
{
private:
	std::string m_username;
	time_t msgTime;
	Room* roomOfOser;
public:
	LoggedUser(std::string username) : m_username(username){};
	~LoggedUser() {};

	std::string getUsername();
	time_t getMsgTime();
	void setMsgTime(time_t time);
	Room* getRoom()const;
	void changeRoom(Room* Room);
	void removeRoom();
};

