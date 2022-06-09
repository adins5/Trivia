#pragma once
#include <string>
#include <list>
#include <vector>


struct Question {
	std::string question;
	std::string answers[4];
	int corrAnsPos;
};


class IDatabase
{
public:
	virtual ~IDatabase() = default;

	virtual bool doesUserExists(std::string userName) = 0;
	virtual bool doesPasswordMatch(std::string userName, std::string password) = 0;
	virtual bool addNewUser(std::string username, std::string password, std::string email) = 0;

	virtual std::list<Question> getQuestions(int dontKnow) = 0;
	virtual float getPlayerAverageAnswerTime(std::string name) = 0;
	virtual int getNumOfCorrectAnswer(std::string name) = 0;
	virtual int getNumOfTotalAnswers(std::string name) = 0;
	virtual int getNumOfPlayerGames(std::string name) = 0;
	virtual int getPlayerScore(std::string name) = 0;
	virtual std::vector<std::string> getHighScores() = 0;


	virtual bool open() = 0;
	virtual void close() = 0;
};