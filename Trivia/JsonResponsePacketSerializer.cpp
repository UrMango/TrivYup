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
