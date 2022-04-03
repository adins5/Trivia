#pragma once
#include "Communicator.h"

class MessageHandler {
public:
	MessageHandler();
	void sendMsg(std::string msg, SOCKET clientSoc);
	RequestInfo& recvMsg(SOCKET clientSoc);


private:

	SOCKET _clientSoc;

};