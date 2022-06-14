#include "RoomAdminRequestHandler.h"

bool RoomAdminRequestHandler::isRequestRelevant(const RequestInfo& request) const
{
	return (request.msgCode == CLOSE_ROOM || request.msgCode == START_GAME || request.msgCode == GET_ROOM_STATE);
}