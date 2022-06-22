#pragma once

class LoginResponse
{
public:
	unsigned int status;
	LoginResponse(unsigned int _status) : status(_status) {};
};
