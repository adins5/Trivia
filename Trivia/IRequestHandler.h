#pragma once
#include "Communicator.h"

class Communicator;

class IRequestHandler {
public:
	IRequestHandler();
	~IRequestHandler();
	virtual bool isRequestRelevant(RequestInfo info) = 0;
	virtual RequestResult handleRequest(RequestInfo info) = 0;
};