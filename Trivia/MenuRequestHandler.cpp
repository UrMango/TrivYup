#include "MenuRequestHandler.h"


MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& handlerFactory) : m_handlerFactory(handlerFactory){}

MenuRequestHandler::~MenuRequestHandler() {}

bool MenuRequestHandler::isRequestRelevant(const RequestInfo& request) const
{
	return (request.msgCode == MT_CLIENT_LOG_IN || request.msgCode == MT_CLIENT_SIGN_UP);
}


RequestResult MenuRequestHandler::handleRequest(const RequestInfo& request) const
{
	std::string msg;
	struct RequestResult result;

	if (!(this->isRequestRelevant(request)))
	{
		//insert field to RequestInfo struct
		result.msg = JsonResponsePacketSerializer::serializeErrorResponse(ErrorResponse("You must first log in or sign up"));
		result.newHandler = nullptr;
	}
	return result;
}
