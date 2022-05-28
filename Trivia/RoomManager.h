#pragma once
//#include <string>
//#include "Helper.h"
//#include <vector>
#include "Room.h"
#include <map>

class RoomManager
{
public:
	void createRoom(LoggedUser, RoomData);
	void deleteRoom(int ID);
	unsigned int getRoomState(int ID);
	std::vector<RoomData>getRooms();
private:
	std::map<unsigned int, Room> m_rooms;
};
