#pragma once
#include "Server.h"
#include "Communicator.h"
#include "LoginRequestHandler.h"
#include "WSAInitializer.h"


int main()
{
	WSAInitializer wsaInit;
	Server server;
	server.run();



}
