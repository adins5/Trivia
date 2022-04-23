#pragma once

#include <string>
#include <WinSock2.h>

class Communicator;

class MessageHandler {
public:
	MessageHandler() = default;
	void sendMsg(std::string msg, SOCKET clientSoc);
	struct RequestInfo* recvMsg(SOCKET clientSoc);

};