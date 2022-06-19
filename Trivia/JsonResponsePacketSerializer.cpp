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
	json["rooms"] = GetRoomResponse.rooms;
	return json.dump();
}


std::string JsonResponsePacketSerializer::serializeGetPlayersInRoomrResponse(GetPlayersInRoomResponse playersInRoomResponse)
{

	nlohmann::json json;
	json["id"] = (int)ResponseCode::PlayersInRoom;
	json["status"] = playersInRoomResponse.status;
	json["players"] = playersInRoomResponse.players;
	return json.dump();
}


std::string JsonResponsePacketSerializer::serializejoinRoomResponse(JoinRoomResponse joinRoomResponse)
{
	nlohmann::json json;
	json["id"] = (int)ResponseCode::JoinRoom;
	json["status"] = joinRoomResponse.status;
	return json.dump();
}

std::string JsonResponsePacketSerializer::serializecreateRoomResponse(CreateRoomResponse createRoomResponse)
{
	nlohmann::json json;
	json["id"] = (int)ResponseCode::createRoom;
	json["status"] = createRoomResponse.status;
	json["roomData"] = createRoomResponse.data;
	return json.dump();
}

std::string JsonResponsePacketSerializer::serializeGetStatisticsResponse(GetStatisticsResponse StatisticsResponse)
{
	nlohmann::json json;
	json["id"] = (int)ResponseCode::GetStatistics;
	json["statistics"] = StatisticsResponse.statistics;
	return json.dump();
}
std::string JsonResponsePacketSerializer::serializeGetPersonalStatsResponse(GetPersonalStatsResponse getPersonalStats)
{
	nlohmann::json json;
	json["id"] = (int)ResponseCode::PersonalStats;
	json["statistics"] = getPersonalStats.statistics;
	return json.dump();
}

std::string JsonResponsePacketSerializer::serializeCloseRoomResponse(CloseRoomResponse closeRoomResponse)
{
	nlohmann::json json;
	json["id"] = (int)ResponseCode::CloseRoom;
	json["status"] = closeRoomResponse.status;
	return json.dump();
}

std::string JsonResponsePacketSerializer::serializeStartGameResponse(StartGameResponse startGameResponse)
{
	nlohmann::json json;
	json["id"] = (int)ResponseCode::StartGame;
	json["status"] = startGameResponse.status;
	return json.dump();
}


std::string JsonResponsePacketSerializer::serializeGetRoomStateResponse(GetRoomStateResponse getRoomStateResponse)
{
	nlohmann::json json;
	json["id"] = (int)ResponseCode::GetRoomState;
	json["status"] = getRoomStateResponse.status;
	json["hasGameBegun"] = getRoomStateResponse.hasGameBegun;
	json["players"] = getRoomStateResponse.players;
	json["questionCount"] = getRoomStateResponse.questionCount;
	json["answerTimeout"] = getRoomStateResponse.answerTimeout;
	return json.dump();
}

std::string JsonResponsePacketSerializer::serializeLeaveRoomResponse(LeaveRoomResponse leaveRoomResponse)
{
	nlohmann::json json;
	json["id"] = (int)ResponseCode::LeaveRoom;
	json["status"] = leaveRoomResponse.status;
	return json.dump();
}

std::string JsonResponsePacketSerializer::serializeGetGameResultsResponse(GetGameResultsResponse getGameResultsResponse)
{
	nlohmann::json json;
	json["id"] = (int)ResponseCode::GetGameResult;
	json["status"] = getGameResultsResponse.status;
	json["results"] = getGameResultsResponse.results;
	return json.dump();
}

std::string JsonResponsePacketSerializer::serializeSubmitAnswerResponse(SubmitAnswerResponse submitAnswerResponse)
{
	nlohmann::json json;
	json["id"] = (int)ResponseCode::SubmitAnswer;
	json["status"] = submitAnswerResponse.status;
	json["correctAnswer"] = submitAnswerResponse.correctAnswer;
	return json.dump();
}

std::string JsonResponsePacketSerializer::serializeGetQuestionResponse(GetQuestionResponse getQuestionResponse)
{
	nlohmann::json json;
	json["id"] = (int)ResponseCode::GetQuestions;
	json["status"] = getQuestionResponse.status;
	json["answers"] = getQuestionResponse.answers;
	json["question"] = getQuestionResponse.question;
	return json.dump();
}

std::string JsonResponsePacketSerializer::serializeLeaveGameResponse(LeaveGameResponse leaveGameResponse)
{
	nlohmann::json json;
	json["id"] = (int)ResponseCode::LeaveGame;
	json["status"] = leaveGameResponse.status;
	return json.dump();
}

std::string JsonResponsePacketSerializer::serializeIsEveryoneAnsweredResponse(GetIsEveryoneAnsweredResponse getIsEveryoneAnsweredResponse)
{
	nlohmann::json json;
	json["id"] = (int)ResponseCode::EveryOneAnswered;
	json["isEveryoneAnswered"] = getIsEveryoneAnsweredResponse.isEveryoneAnswered;
	return json.dump();
}
