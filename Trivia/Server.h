#pragma once

#include "Communicator.h"
#include "SqliteDataBase.h"
#include "RequestHandlerFactory.h"

class Server {
private:
	Communicator m_communicator;
	IDatabase* m_databse;
	RequestHandlerFactory m_handlerFactory;

public:
	inline Server(IDatabase* database, RequestHandlerFactory handlerFactory) : m_databse(database), m_handlerFactory(handlerFactory), m_communicator(m_handlerFactory) {}
	void run();
};