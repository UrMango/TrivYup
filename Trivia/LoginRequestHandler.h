#pragma once
#include "IRequestHandler.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"
#include "RequestHandlerFactory.h"
#include "Helper.h"
#include "LoginManager.h"
#include "LoggedUser.h"

class RequestHandlerFactory;


class LoginRequestHandler : public IRequestHandler
{
public:
	LoginRequestHandler(RequestHandlerFactory& handlerFactory, LoginManager& loginManager);
	~LoginRequestHandler();

	virtual bool isRequestRelevant(const RequestInfo& request) const override;
	virtual RequestResult handleRequest(const RequestInfo& request) override;
	LoggedUser& getUser() const;

private:
	LoginManager& m_loginManager;
	RequestHandlerFactory& m_handlerRequest;
	RequestResult signUp(const RequestInfo request)const;
	RequestResult login(const RequestInfo request)const;
};


