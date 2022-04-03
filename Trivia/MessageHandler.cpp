#include "MessageHandler.h"
#include <string>
#define BUFFLEN 265

MessageHandler::MessageHandler()
{
}

RequestInfo& MessageHandler::recvMsg(SOCKET clientSoc)
{
	RequestInfo msg;

	char buff[BUFFLEN] = "";
	if (recv(clientSoc, buff, BUFFLEN, 0) == INVALID_SOCKET)
	{
		throw std::exception("Error while sending message to client");
	}

	msg.id = buff[0];
	std::string strMsg(buff);
	int len = stoi(strMsg.substr(1, 4));
	msg.buffer = std::vector<unsigned char>(strMsg.begin(), strMsg.begin() + len + 5);
	msg.ctime = time(0);

	return msg;
}

