#pragma once
#include "IRequestHandler.h"
#include "Helper.h"

class LoginRequestHandler : IRequestHandler
{
public:
	bool isRequestRelevant(RequestInfo reuest);
	//RequestResult handleRequest(RequestInfo reuest);

private:
};

