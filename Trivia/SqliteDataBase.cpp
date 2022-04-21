#include <iostream>
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
	if (!isDB())
		return;
}


bool SqliteDataBase::isCorrectPassword(std::string userName, std::string password)
{
}


bool SqliteDataBase::addNewUser(std::string userName, std::string password, std::string email) 
{
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
		std::string ddl("CREATE TABLE USERS(ID INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL, NAME TEXT NOT NULL); \
						CREATE TABLE ALBUMS(ID INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL, NAME TEXT NOT NULL, USER_ID INTEGER NOT NULL, CREATION_DATE TEXT NOT NULL, FOREIGN KEY(USER_ID) REFERENCES USERS(ID)); \
						CREATE TABLE PICTURES(ID  INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, NAME TEXT  NOT NULL, LOCATION TEXT NOT NULL, CREATION_DATE TEXT NOT NULL, ALBUM_ID INTEGER NOT NULL, FOREIGN KEY(ALBUM_ID) REFERENCES ALBUMS(ID)); \
						CREATE TABLE TAGS(PICTURE_ID INTEGER NOT NULL, USER_ID INTEGER NOT NULL, PRIMARY KEY(PICTURE_ID, USER_ID), FOREIGN KEY(PICTURE_ID) REFERENCES PICTURES(ID), FOREIGN KEY(USER_ID) REFERENCES USERS(ID));");
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