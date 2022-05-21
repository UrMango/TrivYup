#include "JsonRequestPacketDeserializer.h"
using std::string;
#include <json.hpp>

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(string userMsg)
{
	// create fason object from string 
	nlohmann::json j = nlohmann::json::parse(userMsg);
	//insert field to struct
	//struct LoginRequest login;
	string pp = j["passward"];
	//login.passward = j["passward"];
	//login.username = j["username"];
	struct LoginRequest login;
	return login;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(string userMsg)
{
	// create fason object from string 
	nlohmann::json j = nlohmann::json::parse(userMsg);

	//insert field to struct
	struct SignupRequest signUp;
	signUp.passward = j["passward"];
	signUp.username = j["username"];
	signUp.email = j["email"];
	return signUp;
}
