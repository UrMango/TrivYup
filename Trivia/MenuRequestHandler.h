#pragma once
#include "IRequestHandler.h"
#include "LoggedUser.h"
#include "RequestHandlerFactory.h"
#include "Helper.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonResponsePacketSerializer.h"
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
	RequestResult signout(const RequestInfo& request);
	RequestResult getRooms(const RequestInfo& request);
	RequestResult getPlayersInRoom(const RequestInfo& request);
	RequestResult getPersonalStats(const RequestInfo& request);
	RequestResult getHighScore(const RequestInfo& request);
	RequestResult joinRoom(const RequestInfo& request);
	RequestResult createRoom(const RequestInfo& request);
	LoggedUser& getUser() const;


public:
	MenuRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser& m_user);
	~MenuRequestHandler();

	virtual bool isRequestRelevant(const RequestInfo& request) const override;
	virtual RequestResult handleRequest(const RequestInfo& request) override;
	virtual unsigned short getType() const override;
};