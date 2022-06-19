#include "RoomMemberRequestHandler.h"
#include "Response.h"
#include "Communicator.h"

bool RoomMemberRequestHandler::isRequestRelevant(struct RequestInfo info)
{
	if (info.id == LEAVE_ROOM || info.id == ROOM_STATE)
	{
		return true;
	}
	return false;
}

RequestResult* RoomMemberRequestHandler::handleRequest(struct RequestInfo info, SOCKET soc)
{
	RequestResult* req = new RequestResult;

	switch (info.id)
	{
	case LEAVE_ROOM:
	{
		req = RoomMemberRequestHandler::leaveRoom(info, soc);
		break;
	}
	case ROOM_STATE:
	{
		req = RoomMemberRequestHandler::getRoomState(info, soc);
		break;
	}
	default:
		break;
	}

	return req;
}


RequestResult* RoomMemberRequestHandler::leaveRoom(RequestInfo info, SOCKET soc)
{
	RequestResult* ret = new RequestResult;
	LeaveRoomResponse* res = new LeaveRoomResponse;
	ret->buffer = info.buffer;
	res->status = LEAVE_ROOM;

	m_room.removeUser(m_user);

	ret->newHandler = (IRequestHandler*)m_HandlerFactory.createMenuRequestHandler(m_user);
	MessageHandler::sendMsg(JsonResponsePacketSerializer::serializeResponse(*res), soc);

	return ret;
}


RequestResult* RoomMemberRequestHandler::getRoomState(RequestInfo info, SOCKET soc)
{
	RequestResult* ret = new RequestResult;
	GetRoomStateResponse* res = new GetRoomStateResponse;
	ret->buffer = info.buffer;
	res->status = ROOM_STATE;
	RoomData data = m_room.getData();

	res->answerTimeOut = data.timePerQuestion;
	res->questionCount = data.numOfQuestionsInGame;
	res->hasGameBegun = data.isActive;
	res->players = m_room.getAllUsers();
	res->gameover = data.gameover;

	ret->newHandler = (IRequestHandler*)m_HandlerFactory.createRoomMemberRequestHandler(m_user, data.id);
	MessageHandler::sendMsg(JsonResponsePacketSerializer::serializeResponse(*res), soc);

	return ret;
}