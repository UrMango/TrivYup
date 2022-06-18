#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDatabase* database) : m_database(database)
{
	this->m_loginManager = new LoginManager(this->m_database);
	this->m_statisticsManager = new StatisticsManager(this->m_database);
	this->m_roomManager = new RoomManager();
	this->m_gameManager = new GameManager(this->m_database);
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler() const
{
	RequestHandlerFactory* requestHandlerFactory = (RequestHandlerFactory*)this;
	return (LoginRequestHandler*)new LoginRequestHandler(*requestHandlerFactory, *this->m_loginManager);
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(LoggedUser& m_user)const
{
	RequestHandlerFactory* requestHandlerFactory = (RequestHandlerFactory*)this;
	return (MenuRequestHandler*)new MenuRequestHandler(*requestHandlerFactory, m_user);
}

RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(LoggedUser& m_user, Room& room)const
{
	RequestHandlerFactory* requestHandlerFactory = (RequestHandlerFactory*)this;
	return (RoomAdminRequestHandler*)new RoomAdminRequestHandler(*requestHandlerFactory, m_user);
}

RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler(LoggedUser& m_user, Room& room) const
{
	RequestHandlerFactory* requestHandlerFactory = (RequestHandlerFactory*)this;
	return (RoomMemberRequestHandler*)new RoomMemberRequestHandler(*requestHandlerFactory, m_user);
}

GameRequestHandler* RequestHandlerFactory::createGameRequestHandler(LoggedUser& user, Room& room, Game& game, GameManager& gameManager) const
{
	RequestHandlerFactory* requestHandlerFactory = (RequestHandlerFactory*)this;
	return (GameRequestHandler*)new GameRequestHandler(game, user, gameManager, *requestHandlerFactory);
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
