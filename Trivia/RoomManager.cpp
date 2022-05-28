#include "RoomManager.h"


void RoomManager::createRoom(const LoggedUser user, const  RoomData roomData)
{
	m_rooms.insert(std::pair<unsigned int, Room&>(_roomID, *(new Room(user, roomData))));

}

