#pragma once
#pragma comment(lib, "Ws2_32.lib")

#include "LoginRequestHandler.h"
#include <iostream>
#include <map>
#include <exception>
#include <WinSock2.h>
#include <string>
#include <thread>
#include <time.h>
#include <vector>
#include "MessageHandler.h"
#include "Request.h"
#include "Response.h"

#define ERR 0
#define LOGIN 1
#define SIGN 2
#define LOGOUT 3

class IRequestHandler;

struct RequestInfo {
	int id;
	time_t ctime;
	std::vector<unsigned char> buffer;
} typedef RequestInfo;


struct RequestResult {
	std::vector<unsigned char> buffer;
	IRequestHandler* newHandler;

}typedef RequestResult;

class Communicator {
private:
	SOCKET m_serverSocket;
	std::map<SOCKET, IRequestHandler*> m_clients;
	int bindAndListen();
	void handleNewClient(SOCKET soc);
	MessageHandler msgHelper;

public:
	Communicator();
	void startHandleRequests();

};

