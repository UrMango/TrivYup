#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDatabase* database) : m_database(database)
{
	this->m_loginManager = new LoginManager(this->m_database);
	this->m_statisticsManager = new StatisticsManager(this->m_database);
	this->m_roomManager = new RoomManager();
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	RequestHandlerFactory* rr = (RequestHandlerFactory*)this;
	return (LoginRequestHandler*)new LoginRequestHandler(*rr, *this->m_loginManager);
}

LoginManager& RequestHandlerFactory::getLoginManager() const
{
	return *(this->m_loginManager);
}

StatisticsManager& RequestHandlerFactory::getStatisticsManager() const
{
	return *(this->m_statisticsManager);
}

IDatabase& RequestHandlerFactory::getIDatabase() const
{
	return *(this->m_database);
}

RoomManager& RequestHandlerFactory::getRoomManager() const
{
	return *(this->m_roomManager);
}
