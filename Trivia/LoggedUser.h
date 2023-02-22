#pragma once
#include <string>

class LoggedUser
{
public:
	LoggedUser(std::string username) : m_username(username) {}
	~LoggedUser() {}

	inline std::string getUsername() { return m_username; }
	bool operator==(LoggedUser other);

private:
	std::string m_username;
};

