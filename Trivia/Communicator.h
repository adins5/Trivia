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

class IRequestHandler;
class LoginRequestHandler;
class MessageHandler;
class JsonResponsePacketSerializer;
class JsonRequestPacketDeserializer; 

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

public:
	Communicator();
	void startHandleRequests();
};

