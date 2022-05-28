#include "Room.h"

Room::Room(const LoggedUser user, const RoomData roomData) : m_metadata(roomData)
{
	this->m_users.push_back(user); 
}

void Room::addUser(LoggedUser user)
{
	this->m_users.push_back(user);
}

void Room::removeUser(LoggedUser user)
{
	for (int i = 0; i < this->m_users.size(); i++)
	{
		if (this->m_users[i].getUsername() == user.getUsername())
		{
			this->m_users.erase(this->m_users.begin() + i);
			break;
		}
	}
}

std::vector<string> Room::getAllUsers()
{
	std::vector <std::string> allUsers;
	for (int i = 0; i < this->m_users.size(); i++)
	{
		allUsers.push_back(this->m_users[i].getUsername());
	}
	return allUsers;
}

unsigned int Room::getRoomState()const
{
	return this->m_metadata.isActive;
}
