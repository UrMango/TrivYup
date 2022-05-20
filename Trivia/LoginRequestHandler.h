#pragma once
#include "IRequestHandler.h"
#include "JsonResponsePacketSerializer.h"
#include "Helper.h"

class LoginRequestHandler : IRequestHandler
{
public:
	bool isRequestRelevant(RequestInfo request);
	std::string handleRequest(RequestInfo request);

private:
};

