#include "RoomMemberRequestHandler.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser& m_user) : _roomUser(m_user.getRoom()), m_user(m_user), m_roomManager(handlerFactory.getRoomManager()), m_handlerFactory(handlerFactory) {}

bool RoomMemberRequestHandler::isRequestRelevant(const RequestInfo& request) const
{
	return (request.msgCode == LEAVE_ROOM || request.msgCode == GET_ROOM_STATE);
}

RequestResult RoomMemberRequestHandler::handleRequest(const RequestInfo& request)
{
	struct RequestResult result;

	LeaveRoomResponse leaveRoomResponse;

	if (!(this->isRequestRelevant(request)))
	{
		//insert field to RequestInfo struct
		result.msg = JsonResponsePacketSerializer::serializeErrorResponse(ErrorResponse("Its not a valid request"));
		result.newHandler = nullptr;
		return result;
	}
	switch (request.msgCode) {
	case LEAVE_ROOM:
		this->m_roomManager.removeUserInRoom(m_user.getRoom()->getRoomData().id, m_user);
		m_user.removeRoom();
		leaveRoomResponse.status = 1;
		result.msg = JsonResponsePacketSerializer::serializeLeaveRoomResponse(leaveRoomResponse);
		result.newHandler = nullptr;
		break;
	case GET_ROOM_STATE:
		return getRoomState(request);
		break;
	}
}

RequestResult RoomMemberRequestHandler::getRoomState(const RequestInfo& request)const
{
	GetRoomStateResponse getRoomStateResponse;
	struct RequestResult result;
	getRoomStateResponse.status = 1;
	getRoomStateResponse.hasGameBegun = this->m_roomManager.getRoomState(this->_roomUser->getRoomData().id);
	getRoomStateResponse.answerTimeout = this->_roomUser->getRoomData().timePerQuestion;
	getRoomStateResponse.players = this->m_roomManager.getAllUsersInRoom(this->_roomUser->getRoomData().id);
	getRoomStateResponse.questionCount = this->_roomUser->getRoomData().numOfQuestionsInGame;
	result.msg = JsonResponsePacketSerializer::serializeGetRoomStateResponse(getRoomStateResponse);
	result.newHandler = nullptr;
	return result;
}