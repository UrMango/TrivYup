#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDatabase* database) : m_database(database)
{
	this->m_loginManager = new LoginManager(this->m_database);
	this->m_statisticsManager = new StatisticsManager(this->m_database);
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	RequestHandlerFactory* rr = (RequestHandlerFactory*)this;
	return (LoginRequestHandler*)new LoginRequestHandler(*rr, *this->m_loginManager);
}

LoginManager RequestHandlerFactory::getLoginManager()
{
	return *this->m_loginManager;
}
