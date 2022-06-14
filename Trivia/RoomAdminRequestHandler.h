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
	RoomManager& m_roomManager;

public:
	virtual bool isRequestRelevant(const RequestInfo& request) const override;
	virtual RequestResult handleRequest(const RequestInfo& request) override;
};