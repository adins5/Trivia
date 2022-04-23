#pragma once
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
	virtual bool isRequestRelevant(struct RequestInfo info) = 0;
	virtual RequestResult* handleRequest(struct RequestInfo info) = 0;
};