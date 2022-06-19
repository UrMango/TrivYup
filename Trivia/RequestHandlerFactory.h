#pragma once
#include "LoginRequestHandler.h"
#include "LoginManager.h"
#include "StatisticsManager.h"
#include "RoomManager.h"
#include "MenuRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"
#include "LoggedUser.h"
#include "GameManager.h"
#include "GameRequestHandler.h"

class LoginRequestHandler;
class MenuRequestHandler;
class RoomAdminRequestHandler;
class RoomMemberRequestHandler;
class GameRequestHandler;

class RequestHandlerFactory
{	
public:
	RequestHandlerFactory(IDatabase* database);
	~RequestHandlerFactory() {};

	LoginRequestHandler* createLoginRequestHandler()const;
	MenuRequestHandler* createMenuRequestHandler(LoggedUser& m_user)const;
	RoomAdminRequestHandler* createRoomAdminRequestHandler(LoggedUser& m_user, Room& room)const;
	RoomMemberRequestHandler* createRoomMemberRequestHandler(LoggedUser& m_user, Room& room) const;
	GameRequestHandler* createGameRequestHandler(LoggedUser& user, Game& game, GameManager& gameManage) const;
	LoginManager& getLoginManager() const;
	StatisticsManager& getStatisticsManager() const;
	IDatabase& getIDatabase() const;
	RoomManager& getRoomManager() const;
	GameManager& getGameManager() const;

private:
	LoginManager* m_loginManager;
	StatisticsManager* m_statisticsManager;
	IDatabase* m_database;
	RoomManager* m_roomManager;
	GameManager* m_gameManager;
};
