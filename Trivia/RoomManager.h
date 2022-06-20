#pragma once
#include "Room.h"
#include <map>

class RoomManager
{
public:
	RoomManager(){};
	~RoomManager() {};
	void createRoom(LoggedUser user,const  RoomData roomData);
	void deleteRoom(const int ID);
	unsigned int getRoomState(const int ID)const;
	std::vector<string> getAllUsersInRoom(const int ID)const;
	RoomData* addUserInRoom(const int ID, LoggedUser user)const;
	void removeUserInRoom(const int ID,  LoggedUser user)const;
	std::vector<RoomData> getRooms()const;
	Room* getRoom(const unsigned int IDOfRoom)const;
	void changeRoomState(const int state, const int ID);

private:
	std::map<unsigned int, Room&> m_rooms;
};
