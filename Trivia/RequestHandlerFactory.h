#pragma once

#include "LoginManager.h"
#include "MenuRequestHandler.h"
#include "SqliteDataBase.h"

class LoginRequestHandler;

class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDatabase* database) : m_database(database), m_loginManager(m_database) {}
	~RequestHandlerFactory() = default;

	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler();

	inline LoginManager& getLoginManager() { return m_loginManager; };

private:
	LoginManager m_loginManager;
	IDatabase* m_database;
};
