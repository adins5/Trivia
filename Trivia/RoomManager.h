#pragma once
#include <map>
#include "Room.h"

class roomManager {
public:
	roomManager() : roomId(1) {}
	~roomManager() {}
	void createRoom(LoggedUser user, RoomData data);
	void deleteRoom(int id);
	unsigned int getRoomState(int id);
	std::vector<RoomData> getRooms();

private:
	std::map<int, Room> m_rooms;
	int roomId;
};