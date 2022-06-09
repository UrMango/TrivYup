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
	RoomManager(){};
	~RoomManager() {};
	void createRoom(const LoggedUser user,const  RoomData roomData);
	void deleteRoom(const int ID);
	unsigned int getRoomState(const int ID)const;
	std::vector<string> getAllUsersInRoom(const int ID)const;
	void addUserInRoom(const int ID, const LoggedUser user)const;
	void removeUserInRoom(const int ID, const LoggedUser user)const;

	std::vector<RoomData> getRooms()const;
private:
	std::map<unsigned int, Room&> m_rooms;
};
