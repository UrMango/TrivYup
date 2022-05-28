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
struct CreateRoomRequest{
	std::string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeout;
};
//******************************************************************************************

class JsonRequestPacketDeserializer
{
private:
public:
	static LoginRequest deserializeLoginRequest(string userMsg);
	static SignupRequest deserializeSignupRequest(string userMsg);
};


