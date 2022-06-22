#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "Helper.h"
#include "JsonRequestPacketDeserializer.h"
#include "Game.h"
#include "GameManager.h"

class RequestHandlerFactory;

class GameRequestHandler : public IRequestHandler
{
private:
	Game& m_game;
	LoggedUser& m_user;
	GameManager& m_gameManager;
	RequestHandlerFactory& m_handlerFacroty;

public:
	GameRequestHandler(Game& game, LoggedUser& user, GameManager& gameManager, RequestHandlerFactory& handlerFacroty) : m_game(game), m_user(user), m_gameManager(m_gameManager), m_handlerFacroty(handlerFacroty){};
	~GameRequestHandler() {};
	virtual bool isRequestRelevant(const RequestInfo& request) const override;
	virtual RequestResult handleRequest(const RequestInfo& request) override;
	RequestResult getQuestion(const RequestInfo& request)const;
	RequestResult leaveRoom(const RequestInfo& request)const;
	RequestResult getRoomRes(const RequestInfo& request)const;
	RequestResult closeGame(const RequestInfo& request);
	RequestResult sumbitAns(const RequestInfo& request)const;
	Game& getGame();
	LoggedUser& getUser() const;
	virtual unsigned short getType() const override;
};