#pragma once

#include "IRequestHandler.h"
#include "Communicator.h"

class Communicator;

class LoginRequestHandler : public IRequestHandler {

public:
	LoginRequestHandler();
	~LoginRequestHandler() {};
	bool isRequestRelevant(struct RequestInfo info) override;
	struct RequestResult* handleRequest(struct RequestInfo info) override;
};