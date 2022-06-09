#pragma once

#include "LoginManager.h"
#include "MenuRequestHandler.h"
#include "SqliteDataBase.h"
#include "RoomManager.h"
#include "StatisticsManager.h"

class LoginRequestHandler;

class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDatabase* database) : m_database(database), m_loginManager(database), m_statisticsManager(database) {}
	~RequestHandlerFactory() = default;

	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler();

	inline LoginManager& getLoginManager() { return m_loginManager; };
	inline roomManager& getroomManager() { return m_roomManager; };
	inline StatisticsManager& getStatisticsManager() { return m_statisticsManager; };

private:
	LoginManager m_loginManager;
	IDatabase* m_database;
	roomManager m_roomManager;
	StatisticsManager m_statisticsManager;
};
