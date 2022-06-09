#include "JsonResponsePacketSerializer.h"

std::string JsonResponsePacketSerializer::serializeLoginResponse(LoginResponse response)
{
	nlohmann::json json;
	json["id"] = (int)ResponseCode::login;
	json["status"] = response.status;

	return json.dump();
}

std::string JsonResponsePacketSerializer::serializeSignupResponse(SignupResponse response)
{
	nlohmann::json json;
	json["id"] = (int)ResponseCode::signup;
	json["status"] = response.status;

	return json.dump();
}

std::string JsonResponsePacketSerializer::serializeErrorResponse(ErrorResponse response)
{
	nlohmann::json json;
	json["id"] = (int)ResponseCode::error;
	json["message"] = response.message;

	return json.dump();	
}

std::string JsonResponsePacketSerializer::serializeLogoutResponse(LogoutReponse LogoutResponse)
{
	nlohmann::json json;
	json["id"] = (int)ResponseCode::logout;
	return json.dump();
}

std::string JsonResponsePacketSerializer::serializeGetRoomResponse(GetRoomsResponse GetRoomResponse)
{
	nlohmann::json json;
	json["id"] = (int)ResponseCode::getRooms;
	//json["rooms"] = GetRoomResponse.rooms;
	return json.dump();
}


std::string JsonResponsePacketSerializer::serializeGetPlayersInRoomrResponse(GetPlayersInRoomResponse playersInRoomResponse)
{

	nlohmann::json json;
	json["players"] = playersInRoomResponse.players;
	return json.dump();
}


std::string JsonResponsePacketSerializer::serializejoinRoomResponse(JoinRoomResponse joinRoomResponse)
{
	nlohmann::json json;
	json["id"] = (int)ResponseCode::JoinRoom;
	return json.dump();
}

std::string JsonResponsePacketSerializer::serializecreateRoomResponse(CreateRoomResponse createRoomResponse)
{
	nlohmann::json json;
	json["id"] = (int)ResponseCode::createRoom;
	return json.dump();
}

std::string JsonResponsePacketSerializer::serializeGetStatisticsResponse(GetStatisticsResponse StatisticsResponse)
{
	nlohmann::json json;
	json["id"] = (int)ResponseCode::createRoom;
	return json.dump();
}

