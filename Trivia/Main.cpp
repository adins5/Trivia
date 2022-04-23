#pragma once
#include "Server.h"
#include "Communicator.h"
#include "LoginRequestHandler.h"
#include "WSAInitializer.h"
#include "SqliteDataBase.h"
#include "LoginManager.h"


int main()
{
	SqliteDataBase x;
	LoginManager logList(&x);

	x.open();
	x.addNewUser("liad", "123456", "123");
	logList.login("lid", "123456");
	logList.logout("lia");
	logList.signup("roi", "qwerty", "gmail");
	x.close();

	WSAInitializer wsaInit;
	Server server;
	server.run();



}
