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

	/*
	JsonRequestPacketDeserializer(const string text, const string dictionaryFileName);
	static string encrypt(const string text, const string dictionaryFileName);
	static string decrypt(const string text, const string dictionaryFileName);
	string encrypt();
	string decrypt();
	friend ostream& operator<<(ostream& os, const SubstitutionText& dt);
	string getText() const;
	*/
};


