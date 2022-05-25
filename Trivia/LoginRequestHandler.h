#pragma once
#include "IRequestHandler.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"
#include "RequestHandlerFactory.h"
#include "Helper.h"
#include "LoginManager.h"

class RequestHandlerFactory;


class LoginRequestHandler : public IRequestHandler
{
public:
	//LoginRequestHandler(LoginManager& loginManager, RequestHandlerFactory& handlerFactory);
	LoginRequestHandler(RequestHandlerFactory& handlerFactory);
	~LoginRequestHandler();

	virtual bool isRequestRelevant(const RequestInfo& request) const override;
	virtual RequestResult handleRequest(const RequestInfo& request)const override;


private:
	LoginManager& m_loginManager;
	RequestHandlerFactory& m_handlerRequest;
	//RequestResult signUp(RequestInfo request);
	//RequestResult login(RequestInfo request);
};


