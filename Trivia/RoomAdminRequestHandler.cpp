#include "RoomAdminRequestHandler.h"

bool RoomAdminRequestHandler::isRequestRelevant(const RequestInfo& request) const
{
	return (request.msgCode == CLOSE_ROOM || request.msgCode == START_GAME || request.msgCode == GET_ROOM_STATE);
}

RequestResult RoomAdminRequestHandler::handleRequest(const RequestInfo& request)
{
	std::string msg;
	struct RequestResult result;

	LeaveRoomResponse leaveRoomResponse;

	StartGameResponse startGameResponse;

	GetRoomStateResponse getRoomStateResponse;
	if (!(this->isRequestRelevant(request)))
	{
		//insert field to RequestInfo struct
		result.msg = JsonResponsePacketSerializer::serializeErrorResponse(ErrorResponse("Its not a valid request"));
		result.newHandler = nullptr;
		return result;
	}
	switch (request.msgCode) {
	case CLOSE_ROOM:
		this->m_roomManager.deleteRoom(this->_roomUser->getRoomData().id);
		leaveRoomResponse.status = 1;
		result.msg = JsonResponsePacketSerializer::serializeLeaveRoomResponse(leaveRoomResponse);
		result.newHandler = nullptr;
		break;
	case START_GAME:
		this->m_roomManager.changeRoomState(1, this->_roomUser->getRoomData().id);
		startGameResponse.status = 1;
		result.msg = JsonResponsePacketSerializer::serializeStartGameResponse(startGameResponse);
		result.newHandler = nullptr;
		break;
	case GET_ROOM_STATE:
		getRoomStateResponse.status = 1;
		getRoomStateResponse.hasGameBegun = this->m_roomManager.getRoomState(this->_roomUser->getRoomData().id);
		getRoomStateResponse.answerTimeout = this->_roomUser->getRoomData().timePerQuestion;
		getRoomStateResponse.players = this->m_roomManager.getAllUsersInRoom(this->_roomUser->getRoomData().id);
		getRoomStateResponse.questionCount = this->_roomUser->getRoomData().numOfQuestionsInGame;
		result.msg = JsonResponsePacketSerializer::serializeGetRoomStateResponse(getRoomStateResponse);
		result.newHandler = nullptr;
		break;
	}
}