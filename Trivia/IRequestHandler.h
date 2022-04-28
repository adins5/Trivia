#pragma once
#include "Communicator.h"
#include <WinSock2.h>
#include <ctime>
#include <vector>


struct RequestInfo {
	int id;
	time_t ctime;
	std::vector<unsigned char> buffer;
};

class IRequestHandler;
struct RequestResult {
	std::vector<unsigned char> buffer;
	IRequestHandler* newHandler;

};

class IRequestHandler {
public:
	virtual bool isRequestRelevant(struct RequestInfo* info) = 0;
	virtual struct RequestResult* handleRequest(struct RequestInfo* info, SOCKET soc) = 0;
};