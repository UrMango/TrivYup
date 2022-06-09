#pragma once
#include "LoginRequestHandler.h"
#include "LoginManager.h"
#include "StatisticsManager.h"
#include "RoomManager.h"
#include "MenuRequestHandler.h"
#include "LoggedUser.h"

class LoginRequestHandler;
class MenuRequestHandler;

class RequestHandlerFactory
{	
public:
	RequestHandlerFactory(IDatabase* database);
	~RequestHandlerFactory() {};

	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler(LoggedUser& m_user);
	LoginManager& getLoginManager() const;
	StatisticsManager& getStatisticsManager() const;
	IDatabase& getIDatabase() const;
	RoomManager& getRoomManager() const;
private:
	LoginManager* m_loginManager;
	StatisticsManager* m_statisticsManager;
	IDatabase* m_database;
	RoomManager* m_roomManager;


};
