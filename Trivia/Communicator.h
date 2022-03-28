#pragma once
#include <WinSock2.h>
#include <iostream>
#include  <map>
#include "IRequestHandler.h"


class Communicator {
	SOCKET m_serverSocket;
	std::map<SOCKET, IRequestHandler*> m_clients;
	int bindAndListen();
	void handleNewClient(SOCKET client);

public:
	void startHandleRequests();

};