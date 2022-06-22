#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "Helper.h"
#include "JsonRequestPacketDeserializer.h"
#include "Room.h"

class RequestHandlerFactory;

class RoomMemberRequestHandler : public IRequestHandler
{
private:
	Room* _roomUser;
	LoggedUser& m_user;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handlerFactory;

public:
	RoomMemberRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser& m_user);
	virtual bool isRequestRelevant(const RequestInfo& request) const override;
	virtual RequestResult handleRequest(const RequestInfo& request) override;

	//getters
	RequestResult leaveRoom(const RequestInfo& request) const;
	virtual unsigned short getType() const override;
	Room* getRoomOfUser();
	LoggedUser& getUser() const;
	RequestResult getRoomState(const RequestInfo& request) const;
};