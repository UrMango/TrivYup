#pragma once
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <json.hpp>
#include <iostream>
#include <vector>
#include <string>

#include "LoginResponse.h"
#include "ErrorResponse.h"

enum ResponseCode
{
	loginSuccess = 1,
	error
};

class JsonResponsePacketSerializer
{	
public:
	static std::string serializeLoginResponse(LoginResponse response);
	static std::string serializeErrorResponse(ErrorResponse response);
};

