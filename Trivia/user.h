#pragma once

#include <string>
#include <iostream>


class User
{
public:

	User(const std::string username, std::string password, std::string email) : m_username(username), m_password(password), m_email(email) {}
	~User() {}

	const std::string& getUsername() const { return m_username; }
	const std::string& getPassword() const { return m_password; }
	const std::string& getEmail() const { return m_email; }

private:
	std::string m_username;
	std::string m_password;
	std::string m_email;
};