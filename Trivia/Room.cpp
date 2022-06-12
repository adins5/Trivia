#include "Room.h"
#include "Response.h"


Room::Room(RoomData data, LoggedUser user) : m_metadata(data)
{
	m_users.push_back(user);
}

int Room::addUser(LoggedUser user)
{
	if (m_metadata.maxPlayers > m_users.size())
	{
		m_users.push_back(user);
		return JOIN_ROOM;
	}
	return ERR;
}

void Room::removeUser(LoggedUser user)
{
	remove(m_users.begin(), m_users.end(), user);
}

std::vector<std::string> Room::getAllUsers()
{
	std::vector<std::string> names;

	for (auto i : m_users)
	{
		names.push_back(i.getUsername());
	}

	return names;
}

RoomData Room::getData()
{
	return m_metadata;
}

