#include "Request.h"
#include "json.hpp"
using json = nlohmann::json;

LoginRequest* JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<unsigned char> buffer)
{
	std::string msg(buffer.begin() + 5, buffer.end());
	json forStruct = *JsonRequestPacketDeserializer::parseHelp(msg);
	
	LoginRequest* req = new LoginRequest;
	req->username = forStruct["username"];
	req->password = forStruct["password"];

	return req;
}

SignupRequest* JsonRequestPacketDeserializer::deserializeSignupRequest(std::vector<unsigned char> buffer)
{
	std::string msg(buffer.begin() + 5, buffer.end());
	json forStruct = *JsonRequestPacketDeserializer::parseHelp(msg);

	SignupRequest* req = new SignupRequest;
	req->username = forStruct["username"];
	req->password = forStruct["password"];
	req->email = forStruct["email"];

	return req;
}

GetPlayersInRoomRequest* JsonRequestPacketDeserializer::deserializeGetPlayersInRoomRequest(std::vector<unsigned char> buffer)
{
	std::string msg(buffer.begin() + 5, buffer.end());
	json forStruct = *JsonRequestPacketDeserializer::parseHelp(msg);

	GetPlayersInRoomRequest* req = new GetPlayersInRoomRequest;
	req->roomId = forStruct["roomId"];

	return req;
}

JoinRoomRequest* JsonRequestPacketDeserializer::deserializeJoinRoomRequest(std::vector<unsigned char> buffer)
{
	std::string msg(buffer.begin() + 5, buffer.end());
	json forStruct = *JsonRequestPacketDeserializer::parseHelp(msg);

	JoinRoomRequest* req = new JoinRoomRequest;
	req->roomId = forStruct["roomId"];

	return req;
}

CreateRoomRequest* JsonRequestPacketDeserializer::deserializeCreateRoomRequest(std::vector<unsigned char> buffer)
{
	std::string msg(buffer.begin() + 5, buffer.end());
	json forStruct = *JsonRequestPacketDeserializer::parseHelp(msg);

	CreateRoomRequest* req = new CreateRoomRequest;
	req->roomName = forStruct["roomName"];
	req->maxUsers = forStruct["maxUsers"];
	req->questionCount = forStruct["questionCount"];
	req->answerTimeout = forStruct["answerTimeout"];

	return req;
}

json* JsonRequestPacketDeserializer::parseHelp(std::string msg)
{
	json* forStruct = new json;
	try
	{
		*forStruct = json::parse(msg);
	}
	catch (json::parse_error& ex)
	{
		std::cerr << "parse error when deserializeing " << ex.byte << std::endl;
	}
	return forStruct;
}