#pragma once

#include <string>
using std::string;

#include "Helper.h"
class Helper;
enum MessageType;
struct RequestInfo;
struct RequestResult;

class IRequestHandler
{
public:
	virtual bool isRequestRelevant(const RequestInfo& request) const = 0;
	virtual RequestResult handleRequest(const RequestInfo& request)const = 0;

private:
};
