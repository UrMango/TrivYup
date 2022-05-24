#pragma once

#include <string>
using std::string;

#include "Helper.h"

class IRequestHandler
{
public:
	virtual bool isRequestRelevant(const RequestInfo& request) const = 0;
	virtual std::string handleRequest(const RequestInfo& request) const = 0;

private:
};

