#pragma once
#include "IRequestHandler.h"
#include "LoggedUser.h"
#include "RequestHandlerFactory.h"
#include "Helper.h"
#include "JsonRequestPacketDeserializer.h"
#include "Room.h"


class RequestHandlerFactory;

class MenuRequestHandler : public IRequestHandler
{
private:
	LoggedUser& m_user;
	RequestHandlerFactory& m_handlerFactory;
	LoginManager& m_loginManager;
	StatisticsManager& m_statisticsManager;
	IDatabase& m_database;
	RoomManager& m_roomManager;
	unsigned int _roomID;


public:
	MenuRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser& m_user);
	~MenuRequestHandler();

	virtual bool isRequestRelevant(const RequestInfo& request) const override;
	virtual RequestResult handleRequest(const RequestInfo& request) override;
};