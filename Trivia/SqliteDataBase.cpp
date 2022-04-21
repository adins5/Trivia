#include <iostream>
#include <sstream>
#include <io.h>

#include "SqliteDataBase.h"


bool SqliteDataBase::isDB()
{
	if (!m_db)
	{
		std::cerr << "No DB selected!" << std::endl;
		return false;
	}

	return true;
}


bool SqliteDataBase::doesUserExists(std::string userName)
{
	bool ret = false;
	
	if (!isDB())
		return ret;
	
	std::stringstream sql;
	sql << "SELECT ID FROM USERS WHERE USERNAME LIKE '" << userName << "';";
	std::cout << sql.str();

	sqlite3_stmt* sth;
	int res = sqlite3_prepare_v2(m_db, sql.str().c_str(), -1, &sth, 0);
	if (res != SQLITE_OK)
	{
		std::cerr << "Err: " << sqlite3_errmsg(m_db) << std::endl;
		return ret;
	}
	
	// fetch
	res = sqlite3_step(sth);
	if (res == SQLITE_ROW)
		ret = true;

	sqlite3_finalize(sth);
	return ret;
}


bool SqliteDataBase::isCorrectPassword(std::string userName, std::string password)
{
	bool ret = false;

	if (!isDB())
		return ret;

	std::stringstream sql;
	sql << "SELECT ID FROM USERS WHERE USERNAME LIKE '" << userName << "' AND PASSWORD LIKE '" << password << "';";
	std::cout << sql.str();

	sqlite3_stmt* sth;
	int res = sqlite3_prepare_v2(m_db, sql.str().c_str(), -1, &sth, 0);
	if (res != SQLITE_OK)
	{
		std::cerr << "Err: " << sqlite3_errmsg(m_db) << std::endl;
		return ret;
	}

	// fetch
	res = sqlite3_step(sth);
	if (res == SQLITE_ROW)
		ret = true;

	sqlite3_finalize(sth);

	return ret;
}


bool SqliteDataBase::addNewUser(User& user)
{
	if (!isDB())
		return false;

	std::stringstream sql;
	char* errMessage = nullptr;
	sql << "INSERT INTO USERS (USERNAME, PASSWORD, EMAIL) VALUES ('" << user.getUsername() << "', '" << user.getPassword() << "', '" << user.getEmail() << "')";

	int res = sqlite3_exec(m_db, sql.str().c_str(), nullptr, nullptr, &errMessage);
	if (res != SQLITE_OK)
	{
		std::cerr << "Err: " << errMessage << std::endl;
		return false;
	}
	return true;
}


bool SqliteDataBase::open()
{
	const std::string dbFileName = "triviaDB.sqlite";
	int file_exist = _access(dbFileName.c_str(), 0);
	int res = sqlite3_open(dbFileName.c_str(), &m_db);
	if (res != SQLITE_OK)
	{
		m_db = nullptr;
		std::cerr << "Failed to open DB" << std::endl;
		return false;
	}
	if (file_exist != 0)
	{
		// init database
		std::string ddl("CREATE TABLE USERS(ID INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL, USERNAME TEXT UNIQUE NOT NULL, PASSWORD TEXT NOT NULL, EMAIL TEXT NULL);");
		char* errMessage = nullptr;
		res = sqlite3_exec(m_db, ddl.c_str(), nullptr, nullptr, &errMessage);
		if (res != SQLITE_OK)
		{
			std::cerr << "Err: " << errMessage << std::endl;
			close();
			return false;
		}
	}

	return true;
}


void SqliteDataBase::close()
{
	sqlite3_close(m_db);
	m_db = nullptr;
}