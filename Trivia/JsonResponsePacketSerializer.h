#pragma once
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <json.hpp>
#include <iostream>
#include <vector>
#include <string>

#include "LoginResponse.h"
#include "ErrorResponse.h"
#include "SignupResponse.h"

enum ResponseCode
{
	error = 0,
	login,
	signup,
};

enum LoginCode
{
	loginSuccess = 0,
	loginError
};

enum SignupCode
{
	signupSuccess = 0,
	signupError
};

class JsonResponsePacketSerializer
{	
public:
	static std::string serializeLoginResponse(LoginResponse response);
	static std::string serializeSignupResponse(SignupResponse response);
	static std::string serializeErrorResponse(ErrorResponse response);
};

