#include "MenuRequestHandler.h"


MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& handlerFactory) : m_handlerFactory(handlerFactory){}

MenuRequestHandler::~MenuRequestHandler() {}

bool MenuRequestHandler::isRequestRelevant(const RequestInfo& request) const
{
	return (request.msgCode == CREATE_ROOM || request.msgCode == GET_ROOMS || request.msgCode == GET_PLAYERS_IN_ROOM || request.msgCode == JOIN_ROOM || request.msgCode == GET_STATISTICS || request.msgCode == LOG_OUT);
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
