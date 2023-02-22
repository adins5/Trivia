#pragma once

#include <string>
#include <WinSock2.h>

class Communicator;

class MessageHandler {
public:
	static void sendMsg(std::string msg, SOCKET clientSoc);
	static struct RequestInfo* recvMsg(SOCKET clientSoc);

};