#pragma once
#include "IRequestHandler.h"
//#include "Communicator.h"

//class Communicator;

class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler() = default;
	~MenuRequestHandler() = default;

	bool isRequestRelevant(RequestInfo info) override { return true; }
	struct RequestResult* handleRequest(RequestInfo info, SOCKET soc) override { RequestResult* x = new RequestResult;  return x; }

private:

};
