#pragma once
#include "Communicator.h"

class Communicator;

class IRequestHandler {
public:
	virtual bool isRequestRelevant(struct RequestInfo info) = 0;
	virtual struct RequestResult* handleRequest(struct RequestInfo info) = 0;
};