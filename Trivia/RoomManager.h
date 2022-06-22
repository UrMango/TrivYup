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
	RoomData* addUserInRoom(const int ID, LoggedUser* user);
	void removeUserInRoom(const int ID,  LoggedUser* user);
	void changeRoomState(const int state, const int ID);

	//getters
	unsigned int getRoomState(const int ID);
	std::vector<string> getAllUsersInRoom(const int ID);
	std::vector<RoomData> getRooms();
	Room* getRoom(const unsigned int IDOfRoom);

private:
	std::mutex _roomsMtx;
	std::map<unsigned int, Room&> m_rooms;
};
