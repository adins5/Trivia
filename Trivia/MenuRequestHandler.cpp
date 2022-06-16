#include "MenuRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "Response.h"
#include "Room.h"


bool MenuRequestHandler::isRequestRelevant(RequestInfo info)
{
	if (info.id == LOGOUT || info.id == ROOMS_RESPONSE || info.id == PLAYERS_IN_ROOM || info.id == HIGH_SCORE || info.id == PERSONAL_STATS || info.id == JOIN_ROOM || info.id == CREATE_ROOM)
	{
		return true;
	}
	return false;
}


RequestResult* MenuRequestHandler::handleRequest(RequestInfo info, SOCKET soc) 
{ 
	RequestResult* req = new RequestResult;

	switch (info.id)
	{
	case LOGOUT:
	{
		req = MenuRequestHandler::signout(info, soc);
		break;
	}

	case ROOMS_RESPONSE:
	{
		req = MenuRequestHandler::getRooms(info, soc);
		break;
	}
	case PLAYERS_IN_ROOM:
	{
		req = MenuRequestHandler::getPlayersInRoom(info, soc);
		break;
	}
	case PERSONAL_STATS:
	{
		req = MenuRequestHandler::getPersonalStats(info, soc);
		break;
	}
	case HIGH_SCORE:
	{
		req = MenuRequestHandler::getHighScore(info, soc);
		break;
	}
	case JOIN_ROOM:
	{
		req = MenuRequestHandler::joinRoom(info, soc);
		break;
	}
	case CREATE_ROOM:
	{
		req = MenuRequestHandler::createRoom(info, soc);
		break;
	}

	}

	return req;
}


RequestResult* MenuRequestHandler::signout(RequestInfo info, SOCKET soc)
{
	RequestResult* ret = new RequestResult;
	LogoutResponse* res = new LogoutResponse;
	ret->buffer = info.buffer;
	res->status = LOGOUT;

	MessageHandler::sendMsg(JsonResponsePacketSerializer::serializeResponse(*res), soc);

	return ret;
}


RequestResult* MenuRequestHandler::getRooms(RequestInfo info, SOCKET soc)
{
	RequestResult* ret = new RequestResult;
	GetRoomsResponse* res = new GetRoomsResponse;
	ret->buffer = info.buffer;

	res->rooms = m_roomManager.getRooms();
	res->status = ROOMS_RESPONSE;

	MessageHandler::sendMsg(JsonResponsePacketSerializer::serializeResponse(*res), soc);

	return ret;
}


RequestResult* MenuRequestHandler::getPlayersInRoom(RequestInfo info, SOCKET soc)
{
	GetPlayersInRoomResponse* res = new GetPlayersInRoomResponse;
	RequestResult* ret = new RequestResult;
	ret->buffer = info.buffer;

	GetPlayersInRoomRequest* req = JsonRequestPacketDeserializer::deserializeGetPlayersInRoomRequest(info.buffer);
	
	Room room = m_roomManager.getRoom(req->roomId);
	res->players = room.getAllUsers();
	
	MessageHandler::sendMsg(JsonResponsePacketSerializer::serializeResponse(*res), soc);

	return ret;
	
}


RequestResult* MenuRequestHandler::getPersonalStats(RequestInfo info, SOCKET soc)
{
	getPersonalStatsResponse* res = new getPersonalStatsResponse;
	RequestResult* ret = new RequestResult;
	ret->buffer = info.buffer;

	res->statistics = m_statisticsManager.getUserStatistics(m_user.getUsername());
	res->status = PERSONAL_STATS;

	MessageHandler::sendMsg(JsonResponsePacketSerializer::serializeResponse(*res), soc);

	return ret;
}


RequestResult* MenuRequestHandler::getHighScore(RequestInfo info, SOCKET soc)
{
	getHighScoreResponse* res = new getHighScoreResponse;
	RequestResult* ret = new RequestResult;
	ret->buffer = info.buffer;

	res->statistics = m_statisticsManager.getHighScore();
	res->status = HIGH_SCORE;

	MessageHandler::sendMsg(JsonResponsePacketSerializer::serializeResponse(*res), soc);

	return ret;
}


RequestResult* MenuRequestHandler::joinRoom(RequestInfo info, SOCKET soc)
{
	JoinRoomResponse* res = new JoinRoomResponse;
	RequestResult* ret = new RequestResult;
	ret->buffer = info.buffer;

	JoinRoomRequest* req = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(info.buffer);
	
	Room room = m_roomManager.getRoom(req->roomId);
	res->status = room.addUser(m_user);
	
	if(res->status != JOIN_ROOM)
	{
		ErrorResponse* err = new ErrorResponse;
		err->message = "Room is full";
		MessageHandler::sendMsg(JsonResponsePacketSerializer::serializeResponse(*err), soc);
		return ret;
	}

	MessageHandler::sendMsg(JsonResponsePacketSerializer::serializeResponse(*res), soc);

	return ret;
}


RequestResult* MenuRequestHandler::createRoom(RequestInfo info, SOCKET soc)
{
	CreateRoomResponse* res = new CreateRoomResponse;
	RequestResult* ret = new RequestResult;
	ret->buffer = info.buffer;

	CreateRoomRequest* req = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(info.buffer);
	
	RoomData data;
	data.id = m_handelFactory.getDatabase().addRoom(req->roomName);
	data.name = req->roomName;
	data.maxPlayers = req->maxUsers;
	data.numOfQuestionsInGame = req->questionCount;
	data.timePerQuestion = req->answerTimeout;
	data.isActive = 0;
	
	int ret = system("py addQuestion.py " + req->questionCount);
	std::clog << "python: " << ret << std::endl;;

	m_roomManager.createRoom(m_user, data);
	res->status = CREATE_ROOM;
	
	MessageHandler::sendMsg(JsonResponsePacketSerializer::serializeResponse(*res), soc);

	return ret;
}
