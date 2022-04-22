#pragma once
#include <vector>

#include "SqliteDataBase.h"
#include "user.h"

class LoggedUser
{
public:
	LoggedUser() {}
	~LoggedUser() { m_loggedUsers.erase(m_loggedUsers.begin(), m_loggedUsers.end()); }

	bool login(std::string username, std::string password, SqliteDataBase& data);
	bool signup(std::string username, std::string password, std::string email, SqliteDataBase& data);
	bool logout(std::string username);

private:
	std::vector<std::string> m_loggedUsers;
};

