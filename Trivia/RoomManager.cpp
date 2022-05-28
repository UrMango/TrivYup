#include "RoomManager.h"


void RoomManager::createRoom(const LoggedUser user, const  RoomData roomData)
{
	m_rooms.insert(std::pair<unsigned int, Room&>(_roomID, *(new Room(user, roomData))));
	_roomID++;
}

void RoomManager::deleteRoom(const int ID)
{
	m_rooms.erase(ID);
}

unsigned int RoomManager::getRoomState(const int ID)const
{
    for (auto& it : m_rooms) {
        if (it.first == ID) {
            return it.second.getRoomState();
        }
    }
}

std::vector<RoomData> RoomManager::getRooms()const
{
    std::vector<RoomData> rooms;
    for (auto& it : m_rooms) {
        if ((it.second.getAllUsers().size() > 0) || (it.second.getRoomState() != 0))
        {
            rooms.push_back(it.second.getRoomData());
        }
    }
    return rooms;
}
