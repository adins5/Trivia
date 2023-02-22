#pragma once
#include <map>
#include "Room.h"

class roomManager {
public:
	roomManager() : roomId(1) {}
	~roomManager() {}
	void createRoom(LoggedUser user, RoomData data);
	void deleteRoom(int id);
	RoomData getRoomState(int id);
	std::vector<RoomData> getRooms();

	inline Room getRoom(int id) { return m_rooms[id]; }

private:
	std::map<int, Room> m_rooms;
	int roomId;
};