#pragma once
#include <WinSock2.h>
#include <iostream>
#include  <map>
#include <thread>
#include "LoginRequestHandler.h"

class Communicator {
	SOCKET m_serverSocket;
	std::map<SOCKET, IRequestHandler*> m_clients;
	int bindAndListen();
	void handleNewClient(SOCKET soc);

public:
	Communicator();
	void startHandleRequests();

};