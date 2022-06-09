#pragma once

#include <fstream>
#include <iostream>

using std::string;
#include <string>

//**************************************structures***************************************
struct LoginRequest {
	string username;
	string passward;
};
struct SignupRequest {
	string username;
	string passward;
	string email;
};
struct JoinRoomRequest {
	unsigned int roomid;
};
struct GetPlayersInRoomRequest {
	unsigned int roomid;
};
/*
struct SubmitAnswerRequest {
	unsigned int answerid;
};*/
struct CreateRoomRequest {
	std::string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeout;
};
struct GetStatisticsRequest {
	unsigned int userid;
};
struct LogOutRoomRequest {
	unsigned int roomid;
};
//******************************************************************************************

class JsonRequestPacketDeserializer
{
private:
public:
	static LoginRequest deserializeLoginRequest(const string userMsg);
	static SignupRequest deserializeSignupRequest(const string userMsg);

	static GetPlayersInRoomRequest deserializeGetPlayersRequest(const string userMsg);
	static JoinRoomRequest deserializeJoinRoomRequest(const string userMsg);
	static CreateRoomRequest deserializeCreateRoomRequest(const string userMsg);
	static int getRequestWithoutData(const string userMsg);
	static GetStatisticsRequest getStatisticsOfUser(const string userMsg);
	static LogOutRoomRequest deserializeLogOutRoomRequest(const string userMsg);

};

