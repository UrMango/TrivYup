#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "Helper.h"
#include "JsonRequestPacketDeserializer.h"
#include "Room.h"
#include "RoomMemberRequestHandler.h"

class RequestHandlerFactory;

class RoomAdminRequestHandler : public IRequestHandler
{
private:

	Room* _roomUser;
	LoggedUser& m_user;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handlerFactory;

public:

	RoomAdminRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser& user);
	virtual bool isRequestRelevant(const RequestInfo& request) const override;
	virtual RequestResult handleRequest(const RequestInfo& request) override;
	RequestResult closeRoom(const RequestInfo& request);
	RequestResult startGame(const RequestInfo& request);

	//getters
	Room* getRoomOfUser();
	LoggedUser& getUser() const;
	RequestResult getRoomState(const RequestInfo& request);
	virtual unsigned short getType() const override;

};