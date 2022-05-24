#pragma once
#include "LoginRequestHandler.h"

class LoginRequestHandler;

class RequestHandlerFactory
{
public:
	//RequestHandlerFactory(IDatabase* dataBase);
	RequestHandlerFactory();
	~RequestHandlerFactory();
	LoginRequestHandler* createLoginRequestHandler();
	//LoginManager& getLoginManager();
private:
	//LoginManager& m_loginManager;
	//IDatabase* m_database;

};
