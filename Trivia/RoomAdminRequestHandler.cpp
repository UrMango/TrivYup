#include "RoomAdminRequestHandler.h"

bool RoomAdminRequestHandler::isRequestRelevant(const RequestInfo& request) const
{
	return (request.msgCode == CLOSE_ROOM || request.msgCode == START_GAME || request.msgCode == GET_ROOM_STATE);
}

RequestResult RoomAdminRequestHandler::handleRequest(const RequestInfo& request)
{
	std::string msg;
	struct RequestResult result;

	if (!(this->isRequestRelevant(request)))
	{
		//insert field to RequestInfo struct
		result.msg = JsonResponsePacketSerializer::serializeErrorResponse(ErrorResponse("Its not a valid request"));
		result.newHandler = nullptr;
		return result;
	}
	switch (request.msgCode) {
	case CLOSE_ROOM:
		
		break;
	}
}