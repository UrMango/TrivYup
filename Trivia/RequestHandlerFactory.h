#pragma once
#include "LoginRequestHandler.h"
#include "LoginManager.h"
#include "StatisticsManager.h"

class LoginRequestHandler;

class RequestHandlerFactory
{	
public:
	RequestHandlerFactory(IDatabase* database);
	~RequestHandlerFactory() {};

	LoginRequestHandler* createLoginRequestHandler();
	LoginManager getLoginManager();
private:
	LoginManager* m_loginManager;
	StatisticsManager* m_statisticsManager;
	IDatabase* m_database;

};
