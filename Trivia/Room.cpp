#include "Room.h"

Room::Room(LoggedUser* user, const RoomData roomData) : m_metadata(roomData)
{
	this->m_users.push_back(user); 
}

RoomData* Room::addUser(LoggedUser* user)
{
	this->m_users.push_back(user);
	return &this->m_metadata;
}

void Room::removeUser(LoggedUser* user)
{
	for (int i = 0; i < this->m_users.size(); i++)
	{
		if (this->m_users[i]->getUsername() == user->getUsername())
		{
			this->m_users.erase(this->m_users.begin() + i);
			break;
		}
	}
}

std::vector<std::string> Room::getAllUsers()
{
	std::vector <std::string> allUsers;
	for (int i = 0; i < this->m_users.size(); i++)
	{
		if(&this->m_users[i])
			allUsers.push_back(this->m_users[i]->getUsername());
	}
	return allUsers;
}

unsigned int Room::getRoomState()const
{
	return this->m_metadata.isActive;
}

RoomData Room::getRoomData()const
{
	return m_metadata;
}


void Room::changeRoomState(const int state)
{
	this->m_metadata.isActive = state;
}

std::vector<LoggedUser*>* Room::getAllLoggedUsers()
{
	return &this->m_users;
}
