#include "RoomManager.h"

void roomManager::createRoom(LoggedUser user, RoomData data)
{
	Room* room = new Room(data, user);
	m_rooms.insert(std::pair<int, Room>(roomId, *room));
	roomId++;
}

void roomManager::deleteRoom(int id)
{
	m_rooms.erase(m_rooms.find(id));
}

unsigned int roomManager::getRoomState(int id)
{
	RoomData data = m_rooms[id].getData();
	return data.isActive;
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
