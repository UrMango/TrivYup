#pragma once
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <json.hpp>
#include <iostream>
#include <vector>
#include <string>

#include "LoginResponse.h"
#include "ErrorResponse.h"
#include "SignupResponse.h"
#include "Helper.h"
#include "Room.h"

enum ResponseCode
{
	error = 0,
	login,
	signup,
	logout,
	JoinRoom,
	createRoom,
	getRooms,
	PlayersInRoom,
	HighScore,
	PersonalStats,
	GetStatistics,
};

enum LoginCode
{
	loginSuccess = 0,
	loginError
};

enum SignupCode
{
	signupSuccess = 0,
	signupError
};

//**************************************structures***************************************
struct LogoutReponse {
	unsigned int status;
};
struct JoinRoomResponse{
	unsigned int status;
};
struct CreateRoomResponse {
	unsigned int status;
};
struct GetRoomsResponse {
	std::vector<RoomData> rooms;
};
struct GetPlayersInRoomResponse{
	unsigned int status;
	std::vector<string> players;
};
struct getHighScoreResponse {
	unsigned int status;
	std::vector<string> statistics;
};
struct getPersonalStatsResponse {
	unsigned int status;
	std::vector<string> statistics;
};

struct GetStatisticsResponse {
	std::vector<std::string> userStats;
};
class JsonResponsePacketSerializer
{	
public:
	static std::string serializeLoginResponse(LoginResponse response);
	static std::string serializeSignupResponse(SignupResponse response);
	static std::string serializeErrorResponse(ErrorResponse response);
	static std::string serializeLogoutResponse(LogoutReponse LogoutResponse);
	static std::string serializeGetRoomResponse(GetRoomsResponse GetRoomResponse);
	static std::string serializeGetPlayersInRoomrResponse(GetPlayersInRoomResponse playersInRoomResponse);
	static std::string serializejoinRoomResponse(JoinRoomResponse joinRoomResponse);
	static std::string serializecreateRoomResponse(CreateRoomResponse createRoomResponse);
	static std::string serializeGetStatisticsResponse(GetStatisticsResponse StatisticsResponse);
};

