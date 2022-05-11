#pragma once

#include <vector>
#include "json.hpp"
#include "RoomManager.h"
using json = nlohmann::json;

#define ERR 0
#define LOGIN 1
#define SIGN 2
#define LOGOUT 3
#define ROOMS_RESPONSE 4
#define PLAYERS_IN_ROOM 5
#define HIGH_SCORE 6
#define PERSONAL_STATS 7
#define JOIN_ROOM 8
#define CREATE_ROOM 9


struct ErrorResponse {
	std::string message;
} typedef ErrorResponse;

struct LoginResponse {
	unsigned int status;
} typedef LoginResponse;

struct SignupResponse {
	unsigned int status;
} typedef SignupResponse;

struct LogoutResponse {
	unsigned int status;
} typedef LogoutResponse;

struct JoinRoomResponse {
	unsigned int status;
} typedef JoinRoomResponse;

struct CreateRoomResponse {
	unsigned int status;
} typedef CreateRoomResponse;

struct GetRoomsResponse {
	unsigned int status;
	std::vector<RoomData> rooms;
} typedef GetRoomsResponse;

struct GetPlayersInRoomResponse {
	std::vector<std::string> players;
} typedef GetPlayersInRoomResponse;

struct getHighScoreResponse {
	unsigned int status;
	std::vector<std::string> statistics;
} typedef getHighScoreResponse;

struct getPersonalStatsResponse {
	unsigned int status;
	std::vector<std::string> statistics;
} typedef getPersonalStatsResponse;

class JsonResponsePacketSerializer {
public:
	static std::string serializeResponse(ErrorResponse res);
	static std::string serializeResponse(SignupResponse res);
	static std::string serializeResponse(LoginResponse res);
	static std::string serializeResponse(LogoutResponse res);
	static std::string serializeResponse(GetRoomsResponse res);
	static std::string serializeResponse(GetPlayersInRoomResponse res);
	static std::string serializeResponse(JoinRoomResponse res);
	static std::string serializeResponse(CreateRoomResponse res);
	static std::string serializeResponse(getPersonalStatsResponse res);
	static std::string serializeResponse(getHighScoreResponse res);
	
	//static std::string serializeResponse(getHighScoreResponse high, getPersonalStatsResponse personal);

private:
	static std::string serializeResponse(json& response, int code);

};
