#pragma once

#include "IDatabase.h"
#include "sqlite3.h"


class SqliteDataBase : public IDatabase
{
public:
	SqliteDataBase() : m_db(nullptr) {}
	~SqliteDataBase() { if (m_db) close(); }

	virtual bool doesUserExists(std::string userName) override;
	virtual bool doesPasswordMatch(std::string userName, std::string password) override;
	virtual bool addNewUser(std::string username, std::string password, std::string email) override;

	virtual bool open() override;
	virtual void close() override;

private:
	bool isDB();
	sqlite3* m_db;
};
