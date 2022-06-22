#include "Room.h"

Room::Room(LoggedUser* user, const RoomData roomData) : m_metadata(roomData)
{
	_roomsMtx = new std::mutex();
	 this->m_users.push_back(user); 
}

RoomData* Room::addUser(LoggedUser* user)
{
	_roomsMtx->lock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
		this->m_users.push_back(user);
	_roomsMtx->unlock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
	return &this->m_metadata;
}

void Room::removeUser(LoggedUser* user)
{
	_roomsMtx->lock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
		for (int i = 0; i < this->m_users.size(); i++)
		{
			if (this->m_users[i]->getUsername() == user->getUsername())
			{
				this->m_users.erase(this->m_users.begin() + i);
				break;
			}
		}
	_roomsMtx->unlock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
}

std::vector<std::string> Room::getAllUsers()
{
	std::vector <std::string> allUsers;
	_roomsMtx->lock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
		for (int i = 0; i < this->m_users.size(); i++)
		{
			if(&this->m_users[i])
				allUsers.push_back(this->m_users[i]->getUsername());
		}
	_roomsMtx->unlock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked=
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
