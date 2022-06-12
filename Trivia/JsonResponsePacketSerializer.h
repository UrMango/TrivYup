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
	CloseRoom, 
	StartGame, 
	GetRoomState,
	LeaveRoom,
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
	RoomData data;
};
struct CreateRoomResponse {
	unsigned int status;
	RoomData data;
};
struct GetRoomsResponse {
	std::vector<RoomData> rooms;
};
struct GetPlayersInRoomResponse{
	unsigned int status;
	std::vector<string> players;
};
struct getHighScoreResponse {
	std::vector<string> statistics;
};
struct GetStatisticsResponse {
	std::vector<std::string> statistics;
};
struct CloseRoomResponse {
	unsigned int status;
};
struct StartGameResponse {
	unsigned int status;
};
struct GetRoomStateResponse {
	unsigned int status;
	bool hasGameBegun;
	std::vector<string> players;
	unsigned int questionCount;
	unsigned int answerTimeout;
};
struct LeaveRoomResponse {
	unsigned int status;
};
struct GetPersonalStatsResponse {
	std::vector<string> statistics;
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
	static std::string serializeGetPersonalStatsResponse(GetPersonalStatsResponse getPersonalStats);
	static std::string serializeCloseRoomResponse(CloseRoomResponse closeRoomResponse);
	static std::string serializeStartGameResponse(StartGameResponse startGameResponse);
	static std::string serializeGetRoomStateResponse(GetRoomStateResponse getRoomStateResponse);
	static std::string serializeLeaveRoomResponse(LeaveRoomResponse leaveRoomResponse);
};

