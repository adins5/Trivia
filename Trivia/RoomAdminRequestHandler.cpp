#include "RoomAdminRequestHandler.h"
#include "Response.h"
#include "Communicator.h"
#include <chrono>
#include <thread>


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
	ret->buffer = info.buffer;
	res->status = CLOSE_ROOM;
	
	RoomData data = m_room.getData();
	data.gameover = true;
	m_room.setData(data);

	std::thread deleteRoom(&RoomAdminRequestHandler::deleteRoomHelper, this);

	ret->newHandler = (IRequestHandler*)m_HandlerFactory.createMenuRequestHandler(m_user);
	MessageHandler::sendMsg(JsonResponsePacketSerializer::serializeResponse(*res), soc);

	return ret;
}


RequestResult* RoomAdminRequestHandler::startGame(RequestInfo info, SOCKET soc)
{
	RequestResult* ret = new RequestResult;
	StartGameResponse* res = new StartGameResponse;
	ret->buffer = info.buffer;
	res->status = START_GAME;

	RoomData data = m_room.getData();
	data.isActive = 1;
	m_room.setData(data);

	ret->newHandler = (IRequestHandler*)m_HandlerFactory.createRoomAdminRequestHandler(m_user, data.id);
	MessageHandler::sendMsg(JsonResponsePacketSerializer::serializeResponse(*res), soc);

	return ret;
}


RequestResult* RoomAdminRequestHandler::getRoomState(RequestInfo info, SOCKET soc)
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

	ret->newHandler = (IRequestHandler*)m_HandlerFactory.createRoomAdminRequestHandler(m_user, data.id);
	MessageHandler::sendMsg(JsonResponsePacketSerializer::serializeResponse(*res), soc);

	return ret;
}


void RoomAdminRequestHandler::deleteRoomHelper()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(300));
	RoomData data = m_room.getData();
	m_roomManager.deleteRoom(data.id);
	m_HandlerFactory.getDatabase()->deleteRoom(data.name);
}