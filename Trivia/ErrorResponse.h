#pragma once
#include <iostream>

class ErrorResponse
{

public:
	std::string message;

	ErrorResponse(std::string msg) : message(msg) {};

};
