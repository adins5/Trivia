#include "Server.h"
#include <string>

Server::Server()
{
}

void Server::run()
{
	std::thread T(&Communicator::startHandleRequests, &m_communicator);
	T.detach();

	std::string userInput = "";
	while (userInput != "EXIT" && userInput != "exit")
	{
		std::getline(std::cin, userInput);
	}
}
