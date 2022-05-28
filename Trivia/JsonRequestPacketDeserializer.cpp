#include "JsonRequestPacketDeserializer.h"
using std::string;
#include <json.hpp>

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(const string userMsg)
{
	// create jason object from string 
	nlohmann::json j = nlohmann::json::parse(userMsg);

	//insert field to struct
	struct LoginRequest login;
	login.passward = j["password"];
	login.username = j["username"];
	return login;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(const string userMsg)
{
	// create jason object from string 
	nlohmann::json j = nlohmann::json::parse(userMsg);

	//insert field to struct
	struct SignupRequest signUp;
	signUp.passward = j["password"];
	signUp.username = j["username"];
	signUp.email = j["email"];
	return signUp;
}

GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersRequest(const string userMsg)
{
	// create fason object from string 
	nlohmann::json j = nlohmann::json::parse(userMsg);

	//insert field to struct
	struct GetPlayersInRoomRequest getPlayersInRoom;
	getPlayersInRoom.roomid = j["roomid"];
	return getPlayersInRoom;
}

JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(const string userMsg)
{
	// create fason object from string 
	nlohmann::json j = nlohmann::json::parse(userMsg);

	//insert field to struct
	struct JoinRoomRequest joinRoomRequest;
	joinRoomRequest.roomid = j["roomid"];
	return joinRoomRequest;
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(const string userMsg)
{
	// create fason object from string 
	nlohmann::json j = nlohmann::json::parse(userMsg);

	//insert field to struct
	struct CreateRoomRequest createRoomRequest;
	createRoomRequest.answerTimeout = j["answerTimeout"];
	createRoomRequest.maxUsers = j["maxUsers"];
	createRoomRequest.questionCount = j["questionCount"];
	createRoomRequest.roomName = j["roomName"];
	return createRoomRequest;
}

int JsonRequestPacketDeserializer::HighScoreRequest(const string userMsg)
{
	// create fason object from string 
	nlohmann::json j = nlohmann::json::parse(userMsg);

	return j["id"];

}
