#include "Response.h"
#include <iostream>
#include <sstream>
#include <iomanip>


#define MSG_LEN_SIZE 4
#define CODE_LEN_SIZE 2

std::string JsonResponsePacketSerializer::serializeResponse(ErrorResponse res)
{
	json response;
	response["message"] = res.message;
	return serializeResponse(response, ERR);
}

std::string JsonResponsePacketSerializer::serializeResponse(SignupResponse res)
{
	json response;
	response["status"] = res.status;
	return serializeResponse(response, SIGN);
}

std::string JsonResponsePacketSerializer::serializeResponse(LoginResponse res)
{
	json response;
	response["status"] = res.status;
	return serializeResponse(response, LOGIN);
}
std::string JsonResponsePacketSerializer::serializeResponse(LogoutResponse res)
{
	json response;
	response["status"] = res.status;
	return serializeResponse(response, LOGOUT);
}

void to_json(json& j, const RoomData& val)
{
	j["id"] = val.id;
	j["name"] = val.name;
	j["maxPlayers"] = val.maxPlayers;
	j["questionCount"] = val.numOfQuestionsInGame;
	j["timePerQuestion"] = val.timePerQuestion;
	j["isActive"] = val.isActive;
	j["gameover"] = val.gameover;
}

std::string JsonResponsePacketSerializer::serializeResponse(GetRoomsResponse res)
{	
	json response;
	response["status"] = res.status;
	response["rooms"] = res.rooms;
	return serializeResponse(response, ROOMS_RESPONSE);
}

std::string JsonResponsePacketSerializer::serializeResponse(GetPlayersInRoomResponse res)
{
	json response;
	response["players"] = res.players;
	return serializeResponse(response, PLAYERS_IN_ROOM);
}

std::string JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse res)
{
	json response;
	response["status"] = res.status;
	return serializeResponse(response, JOIN_ROOM);
}

std::string JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse res)
{
	json response;
	response["status"] = res.status;
	return serializeResponse(response, CREATE_ROOM);
}

std::string JsonResponsePacketSerializer::serializeResponse(getHighScoreResponse res)
{
	json response;
	response["status"] = res.status;
	response["statistics"] = res.statistics;
	return serializeResponse(response, HIGH_SCORE);
}

std::string JsonResponsePacketSerializer::serializeResponse(getPersonalStatsResponse res)
{
	json response;
	response["status"] = res.status;
	response["statistics"] = res.statistics;
	return serializeResponse(response, PERSONAL_STATS);
}

std::string JsonResponsePacketSerializer::serializeResponse(CloseRoomResponse res)
{
	json response;
	response["status"] = res.status;
	return serializeResponse(response, CLOSE_ROOM);
}

std::string JsonResponsePacketSerializer::serializeResponse(StartGameResponse res)
{
	json response;
	response["status"] = res.status;
	return serializeResponse(response, START_GAME);
}

std::string JsonResponsePacketSerializer::serializeResponse(LeaveRoomResponse res)
{
	json response;
	response["status"] = res.status;
	return serializeResponse(response, LEAVE_ROOM);
}

std::string JsonResponsePacketSerializer::serializeResponse(GetRoomStateResponse res)
{
	json response;
	response["status"] = res.status;
	response["players"] = res.players;
	response["hasGameBegun"] = res.hasGameBegun;
	response["questionCount"] = res.questionCount;
	response["answerTimeOut"] = res.answerTimeOut;
	return serializeResponse(response, ROOM_STATE);
}



// helper function to turn the json to vector with the msg code and msg size
std::string JsonResponsePacketSerializer::serializeResponse(json& response, int code)
{
	std::string jsonString = response.dump();
	int len = jsonString.length();

	std::stringstream msgLen;
	msgLen << std::setfill('0') << std::setw(MSG_LEN_SIZE) << len; //

	std::stringstream codeStr;
	codeStr << std::setfill('0') << std::setw(CODE_LEN_SIZE) << code;

	std::string fullMsg = codeStr.str() + msgLen.str() + jsonString;

	return fullMsg;
}


