#include "LoggedUser.h"


bool LoggedUser::login(std::string username, std::string password, SqliteDataBase& data)
{
	if (data.isCorrectPassword(username, password))
	{
		m_loggedUsers.push_back(username);
		return true;
	}
	return false;
}


bool LoggedUser::signup(std::string username, std::string password, std::string email, SqliteDataBase& data)
{
	User newUser(username, password, email);
	if(data.addNewUser(newUser))
	{
		m_loggedUsers.push_back(username);
		return true;
	}
	return false;
}


bool LoggedUser::logout(std::string username)
{
	for(int i = 0; i < m_loggedUsers.size(); ++i)
	{
		if(m_loggedUsers[i] == username)
		{
			m_loggedUsers[i].erase();
			return true;
		}
	}
	return false;
}