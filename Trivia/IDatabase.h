#pragma once
#include <string>

#include "user.h"

class IDatabase
{
public:
	virtual ~IDatabase() = default;

	virtual bool doesUserExists(std::string userName) = 0;
	virtual bool isCorrectPassword(std::string userName, std::string password) = 0;
	virtual bool addNewUser(User& user) = 0;

	virtual bool open() = 0;
	virtual void close() = 0;
};