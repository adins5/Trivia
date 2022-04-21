#include "Communicator.h"
#define PORT 2022
#define BUFFLEN 265


int Communicator::bindAndListen()
{
    struct sockaddr_in sa = { 0 };

	sa.sin_port = htons(PORT); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET
	sa.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will use always "INADDR_ANY"

	// Connects between the socket and the configuration (port and etc..)
	if (bind(m_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");

	// Start listening for incoming requests of clients
	if (listen(m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	std::cout << "Listening on port " << PORT << std::endl;

	while (true)
	{
		//std::cout << "Waiting for client connection request" << std::endl;
		SOCKET client_socket = accept(m_serverSocket, NULL, NULL);
		if (client_socket == INVALID_SOCKET)
			throw std::exception(__FUNCTION__);

		std::cout << "Client accepted. Server and client can speak" << std::endl;
		// the function that handle the conversation with the client
		std::thread T(&Communicator::handleNewClient, this, client_socket); //what function?
		T.detach();
	}
}

void Communicator::handleNewClient(SOCKET soc)
{
	LoginRequestHandler* req = new LoginRequestHandler();
    m_clients.insert(std::pair<SOCKET, IRequestHandler*>(soc, req));

	std::string message = "hello";
	const char* data = message.c_str();
	if (send(soc, data, message.size(), 0) == INVALID_SOCKET)
	{
		throw std::exception("Error while sending message to client");
	}

	char buff[BUFFLEN] = "3";
	if (recv(soc, buff, BUFFLEN, 0) == INVALID_SOCKET)
	{
		throw std::exception("Error while sending message to client");
	}
	std::cout << buff << std::endl;
}

Communicator::Communicator()
{
	m_serverSocket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (m_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");
}

void Communicator::startHandleRequests()
{
	bindAndListen();
}
