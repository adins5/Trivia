#pragma once
#include "Server.h"
#include "Communicator.h"
#include "LoginRequestHandler.h"
#include "WSAInitializer.h"
#include "SqliteDataBase.h"
#include "user.h"
#include "LoggedUser.h"


int main()
{
	SqliteDataBase x;
	LoggedUser logList;
	User user("liad", "123456", "123");
	x.open();
	x.addNewUser(user);
	logList.login("lid", "123456", x);
	logList.logout("lia");
	logList.signup("roi", "qwerty", "gmail", x);
	x.close();

	WSAInitializer wsaInit;
	Server server;
	server.run();



}
