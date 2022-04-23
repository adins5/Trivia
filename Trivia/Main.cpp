#pragma once
#include "Server.h"
#include "Communicator.h"
#include "LoginRequestHandler.h"
#include "WSAInitializer.h"


int main()
{
	WSAInitializer wsaInit;
	IDatabase* database = new SqliteDataBase();

	RequestHandlerFactory handlerFactory(database);

	Server server(database, handlerFactory);
	server.run();

	return 0;
}
