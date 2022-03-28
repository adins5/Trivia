#pragma once
#include "Server.h"
#include "Communicator.h"
#include "LoginRequestHandler.h"

int main()
{
	Server server;
	server.run();
}
