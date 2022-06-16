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
	virtual int addRoom(std::string name);
	virtual bool deleteRoom(std::string name);

	virtual std::list<Question> getQuestions(int dontKnow) override;
	virtual float getPlayerAverageAnswerTime(std::string name) override;
	virtual int getNumOfCorrectAnswer(std::string name) override;
	virtual int getNumOfTotalAnswers(std::string name) override;
	virtual int getNumOfPlayerGames(std::string name) override;
	virtual int getPlayerScore(std::string name) override;
	virtual std::vector<std::string> getHighScores() override;

	virtual bool open() override;
	virtual void close() override;

private:
	bool isDB();
	sqlite3* m_db;
};
