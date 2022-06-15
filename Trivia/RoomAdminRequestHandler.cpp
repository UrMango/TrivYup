#include "RoomAdminRequestHandler.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser& user) : _roomUser(user.getRoom()), m_user(user), m_roomManager(handlerFactory.getRoomManager()), m_handlerFactory(handlerFactory) {}

bool RoomAdminRequestHandler::isRequestRelevant(const RequestInfo& request) const
{
	return (request.msgCode == CLOSE_ROOM || request.msgCode == START_GAME || request.msgCode == GET_ROOM_STATE);
}

RequestResult RoomAdminRequestHandler::handleRequest(const RequestInfo& request)
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
		case CLOSE_ROOM:
			return closeRoom(request);
			break;
		case START_GAME:
			return startGame(request);
			break;
		case GET_ROOM_STATE:
			return getRoomState(request);
			break;
	}
}

Room* RoomAdminRequestHandler::getRoomOfUser()
{
	return this->_roomUser;
}

LoggedUser& RoomAdminRequestHandler::getUser() const
{
	return this->m_user;
}

RequestResult& RoomAdminRequestHandler::closeRoom(const RequestInfo& request)
{
	struct RequestResult result;
	LeaveRoomResponse leaveRoomResponse;
	this->m_roomManager.deleteRoom(this->_roomUser->getRoomData().id);
	m_user.removeRoom();
	leaveRoomResponse.status = 1;
	result.msg = JsonResponsePacketSerializer::serializeLeaveRoomResponse(leaveRoomResponse);
	result.newHandler = nullptr;
	return result;
}

RequestResult& RoomAdminRequestHandler::startGame(const RequestInfo& request)
{
	struct RequestResult result;
	StartGameResponse startGameResponse;
	this->m_roomManager.changeRoomState(1, this->_roomUser->getRoomData().id);
	startGameResponse.status = 1;
	result.msg = JsonResponsePacketSerializer::serializeStartGameResponse(startGameResponse);
	result.newHandler = nullptr;
	return result;
}

RequestResult RoomAdminRequestHandler::getRoomState(const RequestInfo& request)
{
	RoomMemberRequestHandler* MemberRequestHandle = new RoomMemberRequestHandler(m_handlerFactory, m_user);
	return MemberRequestHandle->getRoomState(request);
}