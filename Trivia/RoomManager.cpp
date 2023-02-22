#include "RoomManager.h"

void roomManager::createRoom(LoggedUser user, RoomData data)
{
	Room newRoom(data, user);
	m_rooms[data.id] = newRoom;
	roomId++;
}

void roomManager::deleteRoom(int id)
{
	m_rooms.erase(m_rooms.find(id));
}

RoomData roomManager::getRoomState(int id)
{
	RoomData data = m_rooms[id].getData();
	return data;
}

std::vector<RoomData> roomManager::getRooms()
{
	std::vector<RoomData> data;
	for (auto i : m_rooms)
	{
		data.push_back((i.second).getData());
	}
	return data;
}
