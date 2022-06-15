#pragma once
#include <string>
#include "Helper.h"
#include <vector>
#include "LoggedUser.h"
class LoggedUser;

struct RoomData
{
	unsigned int id = 0;
	std::string name = "";
	unsigned int maxPlayers = 0;
	unsigned int numOfQuestionsInGame = 0;
	unsigned int timePerQuestion = 0;
	unsigned int isActive = 0; //0-not active, 1-active
};

inline void to_json(nlohmann::json& j, const RoomData& rd)
{
	j = { {"id", rd.id},
		{"name", rd.name},
		{"isActive", rd.isActive},
		{"numOfQuestions", rd.numOfQuestionsInGame},
		{"timePerQuestion", rd.timePerQuestion},
		{"maxPlayers", rd.maxPlayers} };
}

class Room
{
public:
	Room(const LoggedUser user,const RoomData roomData);
	RoomData* addUser(LoggedUser user); // adds a user to the users vector
	void removeUser(LoggedUser user); // removes a user from the users vector
	void changeRoomState(const int state);

	// getters
	RoomData getRoomData()const;
	unsigned int getRoomState()const;
	std::vector<string> getAllUsers(); // return a vector of all the users
	std::vector<LoggedUser> getAllLoggedUsers();
private:
	RoomData m_metadata; // the data of the room
	std::vector<LoggedUser> m_users; // the vector of the users in the room
};
