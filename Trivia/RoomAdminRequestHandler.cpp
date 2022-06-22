#include "RoomAdminRequestHandler.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser& user) : _roomUser(user.getRoom()), m_user(user), m_roomManager(handlerFactory.getRoomManager()), m_handlerFactory(handlerFactory)
{}

bool RoomAdminRequestHandler::isRequestRelevant(const RequestInfo& request) const
{
	return (request.msgCode == CLOSE_ROOM || request.msgCode == START_GAME || request.msgCode == GET_ROOM_STATE);
}

//***********************************************************************************************
//the func return a answer for request
//***********************************************************************************************
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

//***********************************************************************************************
//the func close the room the admin created
//***********************************************************************************************
RequestResult RoomAdminRequestHandler::closeRoom(const RequestInfo& request)
{
	struct RequestResult result;
	CloseRoomResponse closeRoomResponse;
	this->m_roomManager.deleteRoom(this->_roomUser->getRoomData().id);
	m_user.removeRoom();
	closeRoomResponse.status = 1;
	result.msg = JsonResponsePacketSerializer::serializeCloseRoomResponse(closeRoomResponse);
	result.newHandler = m_handlerFactory.createMenuRequestHandler(m_user); //change to menu handle
	return result;
}

//***********************************************************************************************
//the func atart the game
//***********************************************************************************************
RequestResult RoomAdminRequestHandler::startGame(const RequestInfo& request)
{
	struct RequestResult result;
	StartGameResponse startGameResponse;
	this->m_roomManager.changeRoomState(1, this->_roomUser->getRoomData().id);

	Game* game = this->m_handlerFactory.getGameManager().createGame(*this->_roomUser);

	startGameResponse.status = 1;
	result.msg = JsonResponsePacketSerializer::serializeStartGameResponse(startGameResponse);
	result.newHandler = this->m_handlerFactory.createGameRequestHandler(m_user, *game, this->m_handlerFactory.getGameManager());
	std::cout << result.msg << std::endl;
	return result;
}

RequestResult RoomAdminRequestHandler::getRoomState(const RequestInfo& request)
{
	RoomMemberRequestHandler* MemberRequestHandle = new RoomMemberRequestHandler(m_handlerFactory, m_user);
	return MemberRequestHandle->getRoomState(request);
}

unsigned short RoomAdminRequestHandler::getType() const
{
	return ReqTypes::ROOM_ADMIN_REQ;
}