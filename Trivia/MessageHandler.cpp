#include "MessageHandler.h"
#include "Communicator.h"
#include <string>
#define BUFFLEN 265

void MessageHandler::sendMsg(std::string msg, SOCKET clientSoc)
{
	const char* data = msg.c_str();
	if (send(clientSoc, data, msg.size(), 0) == INVALID_SOCKET)
	{
		throw std::exception("Error while sending message to client");
	}
}

RequestInfo* MessageHandler::recvMsg(SOCKET clientSoc)
{
	RequestInfo* msg = new RequestInfo;

	char buff[BUFFLEN] = "";
	if (recv(clientSoc, buff, BUFFLEN, 0) == INVALID_SOCKET)
	{
		throw std::exception("Error while sending message to client");
	}

	std::string strMsg(buff);
	msg->id = stoi(strMsg.substr(0,2));
	int len = stoi(strMsg.substr(2, 4));
	msg->buffer = std::vector<unsigned char>(strMsg.begin(), strMsg.begin() + len + 6);
	msg->ctime = time(0);

	return msg;
}

