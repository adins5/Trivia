#pragma once
#include "Server.h"
#include "Communicator.h"
#include "LoginRequestHandler.h"
#include "WSAInitializer.h"
#include "SqliteDataBase.h"
#include "user.h"

int main()
{
	SqliteDataBase x;
	User user("liad", "123456", "123");
	x.open();
	x.addNewUser(user);
	x.doesUserExists("liad");
	x.doesUserExists("h");
	x.isCorrectPassword("liad", "123456");
	x.isCorrectPassword("liad", "12");
	x.close();

	WSAInitializer wsaInit;
	Server server;
	server.run();



}
