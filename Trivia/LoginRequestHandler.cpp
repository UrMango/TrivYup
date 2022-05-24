#include "LoginRequestHandler.h"


LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory& handlerFactory) : m_handlerRequest(handlerFactory){}

LoginRequestHandler::~LoginRequestHandler(){}

bool LoginRequestHandler::isRequestRelevant(const RequestInfo& request) const
{
	return request.msgCode == MT_CLIENT_LOG_IN || request.msgCode == MT_CLIENT_SIGN_UP;
}

std::string LoginRequestHandler::handleRequest(const RequestInfo& request) const
{
	std::string msg;

	if (request.msgCode == MT_CLIENT_LOG_IN)
	{
		LoginRequest pp = JsonRequestPacketDeserializer::deserializeLoginRequest(request.msg); //LoginRequest

		msg = JsonResponsePacketSerializer::serializeLoginResponse(LoginResponse(LoginCode::loginSuccess));
	}
	else if (request.msgCode == MT_CLIENT_SIGN_UP)
	{
		JsonRequestPacketDeserializer::deserializeSignupRequest(request.msg); //SignupRequest

		msg = JsonResponsePacketSerializer::serializeLoginResponse(LoginResponse(SignupCode::signupSuccess));
	}

	return msg;
}
