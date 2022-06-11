#include "MenuRequestHandler.h"


MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser& m_user) : _roomID(1), m_user(m_user), m_handlerFactory(handlerFactory), m_loginManager(handlerFactory.getLoginManager()), m_statisticsManager(handlerFactory.getStatisticsManager()), m_database(handlerFactory.getIDatabase()), m_roomManager(handlerFactory.getRoomManager()){}

MenuRequestHandler::~MenuRequestHandler() {}

bool MenuRequestHandler::isRequestRelevant(const RequestInfo& request) const
{
	return (request.msgCode == CREATE_ROOM || request.msgCode == GET_ROOMS || request.msgCode == GET_PLAYERS_IN_ROOM || request.msgCode == JOIN_ROOM || request.msgCode == GET_STATISTICS || request.msgCode == LOG_OUT);
}

RequestResult MenuRequestHandler::handleRequest(const RequestInfo& request) 
{
	std::string msg;
	struct RequestResult result;

	if (!(this->isRequestRelevant(request)))
	{
		//insert field to RequestInfo struct
		result.msg = JsonResponsePacketSerializer::serializeErrorResponse(ErrorResponse("You must first log in or sign up"));
		result.newHandler = nullptr;
		return result;
	}
	CreateRoomRequest createRoom;
	RoomData roomD;
	RoomData* roomDP;
	CreateRoomResponse createroomResponse;

	GetRoomsResponse getRoomsResponse;

	GetPlayersInRoomRequest getPlayersInRoom;
	GetPlayersInRoomResponse getPlayersInRoomResponse;

	JoinRoomRequest joinRoomRequest;
	JoinRoomResponse JoinRoomResponse;

	GetStatisticsRequest getStatisticsRequest;
	GetStatisticsResponse getStatisticsResponse;

	LogoutReponse logoutReponse;
	LogOutRoomRequest logOutRoomRequest;
	
	switch (request.msgCode) {
		case CREATE_ROOM:
				createRoom = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(request.msg);

			(this->_roomID)++;

			//put data
			roomD.id = _roomID;
			roomD.isActive = 0;
			roomD.maxPlayers = createRoom.maxUsers;
			roomD.name = createRoom.roomName;
			roomD.numOfQuestionsInGame = createRoom.questionCount;
			roomD.timePerQuestion = createRoom.answerTimeout;

			//add room
			m_roomManager.createRoom(this->m_user, roomD);

			//serialize
			createroomResponse.status = 1;
			createroomResponse.data = roomD;

			result.msg = JsonResponsePacketSerializer::serializecreateRoomResponse(createroomResponse);
			result.newHandler = nullptr;
			return result;
			break;
		case GET_ROOMS:
			getRoomsResponse.rooms = m_roomManager.getRooms();
			result.msg = JsonResponsePacketSerializer::serializeGetRoomResponse(getRoomsResponse);
			result.newHandler = nullptr;
			return result;
			break;
		case GET_PLAYERS_IN_ROOM:
			getPlayersInRoom = JsonRequestPacketDeserializer::deserializeGetPlayersRequest(request.msg);
			getPlayersInRoomResponse.status = 1;
			getPlayersInRoomResponse.players = m_roomManager.getAllUsersInRoom(getPlayersInRoom.roomid);
			result.msg = JsonResponsePacketSerializer::serializeGetPlayersInRoomrResponse(getPlayersInRoomResponse);
			result.newHandler = nullptr;
			return result;
			break;
		case JOIN_ROOM:
			joinRoomRequest = JsonRequestPacketDeserializer::deserializeJoinRoomRequest	(request.msg);
			roomDP = m_roomManager.addUserInRoom(joinRoomRequest.roomid, this->m_user);
			if (roomDP) {
				JoinRoomResponse.status = 0;
				JoinRoomResponse.data = *roomDP;
			}
			else
			{
				JoinRoomResponse.status = 1;
			}

			result.msg = JsonResponsePacketSerializer::serializejoinRoomResponse(JoinRoomResponse);
			result.newHandler = nullptr;
			return result;
			break;
		case GET_STATISTICS:
			getStatisticsRequest = JsonRequestPacketDeserializer::getStatisticsOfUser(request.msg);
			getStatisticsResponse.userStats = m_statisticsManager.getUserStatistics(this->m_user.getUsername());
			result.msg = JsonResponsePacketSerializer::serializeGetStatisticsResponse(getStatisticsResponse);
			result.newHandler = nullptr;
			return result;
			break;
		case LOG_OUT:
			logOutRoomRequest = JsonRequestPacketDeserializer::deserializeLogOutRoomRequest(request.msg);
			m_roomManager.addUserInRoom(logOutRoomRequest.roomid, this->m_user);
			logoutReponse.status = 1;
			result.msg = JsonResponsePacketSerializer::serializeLogoutResponse(logoutReponse);
			result.newHandler = nullptr;
			return result;
			break;
		}
	return result;
}
