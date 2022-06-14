#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "Helper.h"
#include "JsonRequestPacketDeserializer.h"
#include "Room.h"

class RoomAdminRequestHandler : public IRequestHandler
{
private:

	Room* _roomUser;
	LoggedUser m_user;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handlerFactory;

public:
	Room* getRoomOfUser();
	LoggedUser getUser() const;
	RoomAdminRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser& m_user);
	virtual bool isRequestRelevant(const RequestInfo& request) const override;
	virtual RequestResult handleRequest(const RequestInfo& request) override;
};