#pragma once

#include "IRequestHandler.h"
#include "LoggedUser.h"
#include "Room.h"
#include "RoomManager.h"
#include "RequestHandlerFactory.h"

class RoomMemberRequestHandler : public IRequestHandler
{
public:
	RoomMemberRequestHandler(Room room, LoggedUser user, roomManager& roomManager, RequestHandlerFactory& HandlerFactory) : m_room(room), m_user(user), m_roomManager(roomManager), m_HandlerFactory(HandlerFactory) {}
	~RoomMemberRequestHandler() = default;

	virtual bool isRequestRelevant(struct RequestInfo info) override;
	virtual RequestResult* handleRequest(struct RequestInfo info, SOCKET soc) override;

	RequestResult* leaveRoom(RequestInfo info, SOCKET soc);
	RequestResult* getRoomState(RequestInfo info, SOCKET soc);

private:
	Room m_room;
	LoggedUser m_user;
	roomManager& m_roomManager;
	RequestHandlerFactory& m_HandlerFactory;
};