#pragma once

#include <fstream>
#include <iostream>

using std::string;

//**************************************structures***************************************
struct LoginRequest {
	string username = "";
	string passward = "";
};
struct SignupRequest {
	string username = "";
	string passward = "";
	string email = "";
};
struct JoinRoomRequest {
	unsigned int roomid = 0;
};
struct GetPlayersInRoomRequest {
	unsigned int roomid = 0;
};
struct SubmitAnswerRequest {
	unsigned int answerid = 0;
};
//******************************************************************************************

class JsonRequestPacketDeserializer
{
private:
public:
	static LoginRequest deserializeLoginRequest(string userMsg);
	static SignupRequest deserializeSignupRequest(string userMsg);
};


