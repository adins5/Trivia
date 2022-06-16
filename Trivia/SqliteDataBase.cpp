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


bool SqliteDataBase::doesPasswordMatch(std::string userName, std::string password)
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


bool SqliteDataBase::addNewUser(std::string username, std::string password, std::string email)
{
	if (!isDB())
		return false;

	std::stringstream sql;
	char* errMessage = nullptr;
	sql << "INSERT INTO USERS (USERNAME, PASSWORD, EMAIL) VALUES ('" << username << "', '" << password << "', '" << email << "')";

	int res = sqlite3_exec(m_db, sql.str().c_str(), nullptr, nullptr, &errMessage);
	if (res != SQLITE_OK)
	{
		std::cerr << "Err: " << errMessage << std::endl;
		return false;
	}
	return true;
}


std::list<Question> SqliteDataBase::getQuestions(int dontKnow)
{
	std::list<Question> retList;
	Question currQue;

	const char* sql = "select b.id, b.question, a.answer, a.corr_ans from answers a inner join questions b on a.q_id=b.id order by a.q_id,a.id";
	sqlite3_stmt* sth;
	
	int res = sqlite3_prepare_v2(m_db, sql, -1, &sth, 0);
	if (res != SQLITE_OK)
	{
		std::cerr << "Err in get questions prepare: " << sqlite3_errmsg(m_db) << std::endl;
		return retList;
	}

	res = sqlite3_step(sth);

	currQue.question = (const char*)sqlite3_column_text(sth, 1);
	int lastId = sqlite3_column_int(sth, 0), currId = 0;
	int count = 0, corr;
	
	while (res == SQLITE_ROW)
	{
		currId = sqlite3_column_int(sth, 0);
		
		if (currId != lastId)
		{
			retList.push_back(currQue);

			currQue.question = (const char*)sqlite3_column_text(sth, 1);
			count = 0;
		}
		
		currQue.answers[count] = (const char*)sqlite3_column_text(sth, 2);
		corr = sqlite3_column_int(sth, 3);
		if(corr)
		{
			currQue.corrAnsPos = count;
		}
		
		++count;
		lastId = currId;
		res = sqlite3_step(sth);
		
	}

	sqlite3_finalize(sth);

	return retList;
}


float SqliteDataBase::getPlayerAverageAnswerTime(std::string name)
{
	float averageTime = 0;
	std::string sql = "select AVG(b.TIME) from USERS a inner join STATISTICS b on b.USER_ID = a.ID WHERE a.USERNAME LIKE \"" + name + "\" group by a.ID";
	sqlite3_stmt* sth;

	int res = sqlite3_prepare_v2(m_db, sql.c_str(), -1, &sth, 0);
	if (res != SQLITE_OK)
	{
		std::cerr << "Err in getPlayerAverageAnswerTime prepare: " << sqlite3_errmsg(m_db) << std::endl;
		return -1;
	}

	res = sqlite3_step(sth);

	
	if (res != SQLITE_ROW)
	{
		return -1;
	}

	averageTime = (float)sqlite3_column_double(sth, 0);


	sqlite3_finalize(sth);

	return averageTime;
}



int SqliteDataBase::getNumOfCorrectAnswer(std::string name)
{
	int corrAns = 0;
	std::string sql = "select count(*) from USERS a inner join STATISTICS b on b.USER_ID = a.ID WHERE a.USERNAME LIKE \"" + name + "\" and b.IS_ANS_CORR = 1";
	sqlite3_stmt* sth;
	
	int res = sqlite3_prepare_v2(m_db, sql.c_str(), -1, &sth, 0);
	if (res != SQLITE_OK)
	{
		std::cerr << "Err in getNumOfCorrectAnswer prepare: " << sqlite3_errmsg(m_db) << std::endl;
		return -1;
	}

	res = sqlite3_step(sth);
	if (res != SQLITE_ROW)
	{
		return -1;
	}

	corrAns = sqlite3_column_int(sth, 0);

	sqlite3_finalize(sth);

	return corrAns;
}


int SqliteDataBase::getNumOfTotalAnswers(std::string name)
{
	int ans = 0;
	std::string sql = "select count(*) from USERS a inner join STATISTICS b on b.USER_ID = a.ID WHERE a.USERNAME LIKE \"" + name + "\"";
	sqlite3_stmt* sth;

	int res = sqlite3_prepare_v2(m_db, sql.c_str(), -1, &sth, 0);
	if (res != SQLITE_OK)
	{
		std::cerr << "Err in getNumOfTotalAnswers prepare: " << sqlite3_errmsg(m_db) << std::endl;
		return -1;
	}

	res = sqlite3_step(sth);
	if (res != SQLITE_ROW)
	{
		return -1;
	}

	ans = sqlite3_column_int(sth, 0);

	sqlite3_finalize(sth);

	return ans;
}


int SqliteDataBase::getNumOfPlayerGames(std::string name)
{
	int numOfGame = 0;
	std::string sql = "select count(distinct b.GAME_ID) from USERS a inner join STATISTICS b on b.USER_ID = a.ID WHERE a.USERNAME LIKE \"" + name + "\"";
	sqlite3_stmt* sth;

	int res = sqlite3_prepare_v2(m_db, sql.c_str(), -1, &sth, 0);
	if (res != SQLITE_OK)
	{
		std::cerr << "Err in getNumOfPlayerGames prepare: " << sqlite3_errmsg(m_db) << std::endl;
		return -1;
	}

	res = sqlite3_step(sth);
	if (res != SQLITE_ROW)
	{
		return -1;
	}

	numOfGame = sqlite3_column_int(sth, 0);

	sqlite3_finalize(sth);

	return numOfGame;
}

int SqliteDataBase::getPlayerScore(std::string name)
{
	int score = 0;
	std::string sql = "select sum(case when b.IS_ANS_CORR = 1 then 1000/b.time+1000 else -200 end) from USERS a inner join STATISTICS b on b.USER_ID = a.ID WHERE a.USERNAME LIKE \"" + name + "\"";
	sqlite3_stmt* sth;

	int res = sqlite3_prepare_v2(m_db, sql.c_str(), -1, &sth, 0);
	if (res != SQLITE_OK)
	{
		std::cerr << "Err in getPlayerScore prepare: " << sqlite3_errmsg(m_db) << std::endl;
		return -1;
	}

	res = sqlite3_step(sth);
	if (res != SQLITE_ROW)
	{
		return -1;
	}

	score = sqlite3_column_int(sth, 0);

	sqlite3_finalize(sth);

	return score;
}


std::vector<std::string> SqliteDataBase::getHighScores() 
{
	std::vector<std::string> highScores;
	std::string name;

	std::string sql = "select a.USERNAME, sum(case when b.IS_ANS_CORR = 1 then 1000/b.time+1000 else -200 end) as score from USERS a inner join STATISTICS b on b.USER_ID = a.ID order by score DESC";
	sqlite3_stmt* sth;

	int res = sqlite3_prepare_v2(m_db, sql.c_str(), -1, &sth, 0);
	if (res != SQLITE_OK)
	{
		std::cerr << "Err in getHighScores prepare: " << sqlite3_errmsg(m_db) << std::endl;
		return highScores;
	}

	res = sqlite3_step(sth);
	while (res == SQLITE_ROW)
	{
		name = (const char*)sqlite3_column_text(sth, 0);
		highScores.push_back(name);
		res = sqlite3_step(sth);
	}
	
	sqlite3_finalize(sth);
	return highScores;
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
		std::string ddl("CREATE TABLE USERS(ID INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL, USERNAME TEXT UNIQUE NOT NULL, PASSWORD TEXT NOT NULL, EMAIL TEXT NULL); \
						 CREATE TABLE STATISTICS(ID INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL, USER_ID INTEGER NOT NULL, GAME_ID INTEGER NOT NULL, TIME INTEGER NOT NULL, IS_ANS_CORR INTEGER NOT NULL, FOREIGN KEY (USER_ID) REFERENCES USERS(ID)); \
						 CREATE TABLE QUESTIONS(ID INTEGER PRIMARY KEY  NOT NULL, QUESTION TEXT NOT NULL) \
						 CREATE TABLE ANSWERS(ID INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL, Q_ID INTEGER NOT NULL, CORR_ANS INTEGER NOT NULL, ANSWER TEXT MOT NULL, FOREIGN KEY(Q_ID) REFERENCES QUESTIONS(ID))");

		
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