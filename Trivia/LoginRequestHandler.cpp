#include "LoginRequestHandler.h"
bool LoginRequestHandler::isRequestRelevant(RequestInfo request)
{
	return request.msgCode == MT_CLIENT_LOG_IN || request.msgCode == MT_CLIENT_SIGN_UP;
}

std::string LoginRequestHandler::handleRequest(RequestInfo request)
{
	std::string msg;

	if (request.msgCode == MT_CLIENT_LOG_IN)
	{
		msg = JsonResponsePacketSerializer::serializeLoginResponse(LoginResponse(LoginCode::loginSuccess));
	}
	else if (request.msgCode == MT_CLIENT_SIGN_UP)
	{
		msg = JsonResponsePacketSerializer::serializeLoginResponse(LoginResponse(SignupCode::signupSuccess));
	}

	return msg;
}