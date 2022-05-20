#include "LoginRequestHandler.h"
bool LoginRequestHandler::isRequestRelevant(RequestInfo reuest)
{
	return reuest.msgCode == MT_CLIENT_LOG_IN || reuest.msgCode == MT_CLIENT_SIGN_UP;
}

/*
RequestResult LoginRequestHandler::handleRequest(RequestInfo reuest)
{
	if (msg_code == MT_CLIENT_LOG_IN)
	{


	}
	else if (msg_code == MT_CLIENT_SIGN_UP)
	{

	}

	msg = new RecvMessage(client_socket, msg_code, values);
	return msg;
}
*/