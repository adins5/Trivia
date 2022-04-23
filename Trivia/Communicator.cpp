#include "Communicator.h"
#include <mutex>          

std::mutex mtx;

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
		std::thread T(&Communicator::handleNewClient, this, client_socket); 
		T.detach();
	}
}

void Communicator::handleNewClient(SOCKET soc)
{
	RequestResult* result = nullptr;
	
	mtx.lock();
    m_clients[soc] =  (IRequestHandler*)m_handlerFactory.createLoginRequestHandler();
	mtx.unlock();

	while (true)
	{
		RequestInfo* msgInfo = m_msgHelper.recvMsg(soc);

		if (!m_clients[soc]->isRequestRelevant(*msgInfo))
		{
			continue;
		}

		result = m_clients[soc]->handleRequest(*msgInfo);

		mtx.lock();
		m_clients[soc] = result->newHandler;
		mtx.unlock();

		std::cout << (char*)&result->buffer[0] << std::endl;
	}
}

Communicator::Communicator(RequestHandlerFactory& handlerFactory) : m_handlerFactory(handlerFactory)
{
	m_serverSocket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");
}

void Communicator::startHandleRequests()
{
	bindAndListen();
}
