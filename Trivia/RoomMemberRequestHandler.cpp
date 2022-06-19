#include "RoomMemberRequestHandler.h"

Room* RoomMemberRequestHandler::getRoomOfUser()
{
	return this->_roomUser;
}

LoggedUser& RoomMemberRequestHandler::getUser() const
{
	return this->m_user;
}

RoomMemberRequestHandler::RoomMemberRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser& m_user) : _roomUser(m_user.getRoom()), m_user(m_user), m_roomManager(handlerFactory.getRoomManager()), m_handlerFactory(handlerFactory) {}

bool RoomMemberRequestHandler::isRequestRelevant(const RequestInfo& request) const
{
	return (request.msgCode == LEAVE_ROOM || request.msgCode == GET_ROOM_STATE);
}

RequestResult RoomMemberRequestHandler::handleRequest(const RequestInfo& request)
{
	struct RequestResult result;

	if (!(this->isRequestRelevant(request)))
	{
		//insert field to RequestInfo struct
		result.msg = JsonResponsePacketSerializer::serializeErrorResponse(ErrorResponse("Its not a valid request"));
		result.newHandler = nullptr;
		return result;
	}
	switch (request.msgCode) {
	case LEAVE_ROOM:
		return leaveRoom(request);
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
	getRoomStateResponse.status = 0;
	getRoomStateResponse.hasGameBegun = this->m_roomManager.getRoomState(this->_roomUser->getRoomData().id);
	getRoomStateResponse.answerTimeout = this->_roomUser->getRoomData().timePerQuestion;
	getRoomStateResponse.players = this->m_roomManager.getAllUsersInRoom(this->_roomUser->getRoomData().id);
	getRoomStateResponse.questionCount = this->_roomUser->getRoomData().numOfQuestionsInGame;
	result.msg = JsonResponsePacketSerializer::serializeGetRoomStateResponse(getRoomStateResponse);
	result.newHandler = nullptr;
	return result;
}

RequestResult RoomMemberRequestHandler::leaveRoom(const RequestInfo& request) const
{
	LeaveRoomResponse leaveRoomResponse;
	struct RequestResult result;
	if (m_user.getRoom()) {
		m_user.getRoom()->removeUser(m_user);
	}
	this->m_user.removeRoom();
	leaveRoomResponse.status = 1;
	result.msg = JsonResponsePacketSerializer::serializeLeaveRoomResponse(leaveRoomResponse);
	result.newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_user);
	return result;
}
