#pragma once

#include <vector>
#include <iostream>
#include "json.hpp"
using json = nlohmann::json;

struct LoginRequest {
	std::string username;
	std::string password;
} typedef LoginRequest;

struct SignupRequest {
	std::string username;
	std::string password;
	std::string email;
} typedef SignupRequest;

struct GetPlayersInRoomRequest {
	unsigned int roomId;
};

struct JoinRoomRequest {
	unsigned int roomId;
};

struct CreateRoomRequest {
	std::string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeout;
};


class JsonRequestPacketDeserializer {
public:
	static LoginRequest* deserializeLoginRequest(std::vector<unsigned char> buffer);
	static SignupRequest* deserializeSignupRequest(std::vector<unsigned char> buffer);
	static GetPlayersInRoomRequest* deserializeGetPlayersInRoomRequest(std::vector<unsigned char> buffer);
	static JoinRoomRequest* deserializeJoinRoomRequest(std::vector<unsigned char> buffer);
	static CreateRoomRequest* deserializeCreateRoomRequest(std::vector<unsigned char> buffer);

private:
	static json* parseHelp(std::string msg);
};