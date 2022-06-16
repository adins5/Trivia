#include "RoomAdminRequestHandler.h"
#include "Response.h"
#include "Communicator.h"


bool RoomAdminRequestHandler::isRequestRelevant(struct RequestInfo info)
{
	if (info.id == CLOSE_ROOM || info.id == START_GAME || info.id == ROOM_STATE)
	{
		return true;
	}
	return false;
}

RequestResult* RoomAdminRequestHandler::handleRequest(struct RequestInfo info, SOCKET soc)
{
	RequestResult* req = new RequestResult;

	switch (info.id)
	{
	case CLOSE_ROOM:
	{
		req = RoomAdminRequestHandler::closeRoom(info, soc);
		break;
	}
	case START_GAME:
	{
		req = RoomAdminRequestHandler::startGame(info, soc);
		break;
	}
	case ROOM_STATE:
	{
		req = RoomAdminRequestHandler::getRoomState(info, soc);
		break;
	}
	default:
		break;
	}

	return req;
}


RequestResult* RoomAdminRequestHandler::closeRoom(RequestInfo info, SOCKET soc)
{
	RequestResult* ret = new RequestResult;
	CloseRoomResponse* res = new CloseRoomResponse;
	LeaveRoomResponse* leaveRes = new LeaveRoomResponse;
	ret->buffer = info.buffer;
	res->status = CLOSE_ROOM;

	RoomData data = m_room.getData();
	std::vector<std::string> users = m_room.getAllUsers();
	for(int i = 0; i < users.size(); ++i)
	{
		
	}
	m_roomManager.deleteRoom(data.id);

	MessageHandler::sendMsg(JsonResponsePacketSerializer::serializeResponse(*res), soc);

	return ret;
}


RequestResult* RoomAdminRequestHandler::startGame(RequestInfo info, SOCKET soc)
{

}


RequestResult* RoomAdminRequestHandler::getRoomState(RequestInfo info, SOCKET soc)
{
	RequestResult* ret = new RequestResult;
	GetRoomStateResponse* res = new GetRoomStateResponse;
	ret->buffer = info.buffer;
	res->status = ROOM_STATE;
	RoomData data = m_roomManager.getRoomState(m_room.getData().id);
	
	res->answerTimeOut = data.timePerQuestion;
	res->questionCount = data.numOfQuestionsInGame;
	res->hasGameBegun = data.isActive;
	res->players = m_room.getAllUsers();

	MessageHandler::sendMsg(JsonResponsePacketSerializer::serializeResponse(*res), soc);

	return ret;
}