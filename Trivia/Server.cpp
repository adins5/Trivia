#include "Server.h"
#include <string>


void Server::run()
{
	std::thread T(&Communicator::startHandleRequests, &m_communicator);
	T.detach();

	std::string userInput = "";
	while (userInput != "EXIT" && userInput != "exit")
	{
		std::getline(std::cin, userInput);
		if (userInput == "show")
		{
			std::cout << "usernames on system: \n";
			std::vector<std::string> names = m_handlerFactory.UserNames();
			for (int i = 0; i < names.size(); i++)
			{
				std::cout << names[i] << "\n";
			}
		}

	}
}
