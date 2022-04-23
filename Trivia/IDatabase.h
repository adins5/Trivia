#pragma once
#include <string>


class IDatabase
{
public:
	virtual ~IDatabase() = default;

	virtual bool doesUserExists(std::string userName) = 0;
	virtual bool doesPasswordMatch(std::string userName, std::string password) = 0;
	virtual bool addNewUser(std::string username, std::string password, std::string email) = 0;

	virtual bool open() = 0;
	virtual void close() = 0;
};