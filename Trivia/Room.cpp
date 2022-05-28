#include "Room.h"

Room::Room(const LoggedUser user, const RoomData roomData) : m_metadata(roomData)
{
	this->m_users.push_back(user); 
}

void Room::addUser(LoggedUser user)
{
	this->m_users.push_back(user);
}