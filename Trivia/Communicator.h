#pragma once
#pragma comment(lib, "Ws2_32.lib")

#include "LoginRequestHandler.h"
#include <iostream>
#include  <map>
#include <exception>
#include <WinSock2.h>
#include <string>
#include <thread>


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