#pragma once

#include "LoginManager.h"
#include "SqliteDataBase.h"
#include "StatisticsManager.h"
#include "RoomManager.h"

class LoginRequestHandler;
class MenuRequestHandler;

class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDatabase* database) : m_database(database), m_loginManager(database), m_statisticsManager(database) {}
	~RequestHandlerFactory() = default;

	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler(LoggedUser user);

	inline LoginManager& getLoginManager() { return m_loginManager; }
	inline roomManager& getroomManager() { return m_roomManager; }
	inline StatisticsManager& getStatisticsManager() { return m_statisticsManager; }
	inline SqliteDataBase getDatabase() { return (SqliteDataBase*)m_database; }

private:
	LoginManager m_loginManager;
	IDatabase* m_database;
	roomManager m_roomManager;
	StatisticsManager m_statisticsManager;
};
