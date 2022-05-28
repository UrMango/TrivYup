#pragma once
//#include <string>
//#include "Helper.h"
//#include <vector>
#include "Room.h"
#include <map>
//#include <map>

class RoomManager
{
public:
	RoomManager(): _roomID(1){};
	~RoomManager() {};
	void createRoom(const LoggedUser user,const  RoomData roomData);
	void deleteRoom(const int ID);
	unsigned int getRoomState(const int ID)const;
	std::vector<RoomData> getRooms()const;
private:
	std::map<unsigned int, Room&> m_rooms;
	unsigned int _roomID;
};
