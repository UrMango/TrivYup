#pragma once
#include "Room.h"
#include <map>

class RoomManager
{
public:
	RoomManager(){};
	~RoomManager() {};
	void createRoom(LoggedUser* user,const  RoomData roomData);
	void deleteRoom(const int ID);
	unsigned int getRoomState(const int ID);
	std::vector<string> getAllUsersInRoom(const int ID);
	RoomData* addUserInRoom(const int ID, LoggedUser* user);
	void removeUserInRoom(const int ID,  LoggedUser* user);
	std::vector<RoomData> getRooms();
	Room* getRoom(const unsigned int IDOfRoom);
	void changeRoomState(const int state, const int ID);

private:
	std::mutex _roomsMtx;
	std::map<unsigned int, Room&> m_rooms;
};
