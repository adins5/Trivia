#include "LoginManager.h"


bool LoginManager::signup(std::string username, std::string password, std::string email)
{

	if (m_database->addNewUser(username, password, email))
	{
		LoggedUser newUser(username);
		m_loggedUsers.push_back(newUser);
		return true;
	}
	return false;
}


bool LoginManager::login(std::string username, std::string password)
{
	if (m_database->doesPasswordMatch(username, password))
	{
		LoggedUser user(username);
		m_loggedUsers.push_back(user);
		return true;
	}
	return false;
}


bool LoginManager::logout(std::string username)
{
	LoggedUser user(username);
	for (int i = 0; i < m_loggedUsers.size(); ++i)
	{
		if (m_loggedUsers[i].getUsername() == user.getUsername())
		{
			m_loggedUsers.erase(m_loggedUsers.begin() + i);
			return true;
		}
	}
	return false;
}