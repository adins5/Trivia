#pragma once
#include <vector>
#include "LoggedUser.h"


struct RoomData {
	unsigned int id;
	std::string name;
	unsigned int maxPlayers;
	unsigned int numOfQuestionsInGame;
	unsigned int timePerQuestion;
	unsigned int isActive;
	bool gameover = false;
} typedef RoomData;


class Room
{
public:
	Room() {}
	Room(RoomData data, LoggedUser user);
	~Room() { m_users.clear(); }

	int addUser(LoggedUser user);
	void removeUser(LoggedUser user);
	std::vector<std::string> getAllUsers();
	
	RoomData getData();
	void setData(RoomData data) { m_metadata = data; }

private:
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;
};

