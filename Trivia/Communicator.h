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
#include "RequestHandlerFactory.h"

class IRequestHandler;
class LoginRequestHandler;
class MessageHandler;
class JsonResponsePacketSerializer;
class JsonRequestPacketDeserializer; 


class Communicator {
private:
	SOCKET m_serverSocket;
	std::map<SOCKET, IRequestHandler*> m_clients;
	MessageHandler m_msgHelper;
	RequestHandlerFactory& m_handlerFactory;

	int bindAndListen();
	void handleNewClient(SOCKET soc);

public:
	Communicator(RequestHandlerFactory& handlerFactory);
	void startHandleRequests();
};

