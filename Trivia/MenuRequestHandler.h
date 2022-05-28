#pragma once
#include "IRequestHandler.h"
#include "LoggedUser.h"
#include "RequestHandlerFactory.h"


class MenuRequestHandler : public IRequestHandler
{
private:
	LoggedUser m_user;
	//RoomManager& m_roomManager;
	//StatisticsManager& m_statisticsManager;
	RequestHandlerFactory& m_handlerFactory;

public:
	MenuRequestHandler(RequestHandlerFactory& handlerFactory);
	~MenuRequestHandler() {};

	virtual bool isRequestRelevant(const RequestInfo& request) const override;
	virtual RequestResult handleRequest(const RequestInfo& request)const override;
};