#include "RoomAdminRequestHandler.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser& user) : _roomUser(m_user.getRoom()), m_user(user), m_roomManager(handlerFactory.getRoomManager()), m_handlerFactory(handlerFactory) {}

bool RoomAdminRequestHandler::isRequestRelevant(const RequestInfo& request) const
{
	return (request.msgCode == CLOSE_ROOM || request.msgCode == START_GAME || request.msgCode == GET_ROOM_STATE);
}

RequestResult RoomAdminRequestHandler::handleRequest(const RequestInfo& request)
{
	struct RequestResult result;

	LeaveRoomResponse leaveRoomResponse;

	StartGameResponse startGameResponse;

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
			m_user.removeRoom();
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
			RoomMemberRequestHandler* MemberRequestHandle = new RoomMemberRequestHandler(m_handlerFactory, m_user);
			MemberRequestHandle->getRoomState(request);
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