#pragma once
#include <vector>

#include "SqliteDataBase.h"
#include "LoggedUser.h"


class LoginManager
{
public:
	LoginManager(IDatabase* database) : m_database(database) {}
	~LoginManager() { m_loggedUsers.erase(m_loggedUsers.begin(), m_loggedUsers.end()); }

	bool signup(std::string username, std::string password, std::string email);
	bool login(std::string username, std::string password);
	bool logout(std::string username);

private:
	IDatabase* m_database;
	std::vector<LoggedUser> m_loggedUsers;
};

