#include "Request.h"
#include "json.hpp"
using json = nlohmann::json;

LoginRequest& JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<unsigned char> buffer)
{
	std::string msg(buffer.begin() + 5, buffer.end());
	json forStruct = json::parse(msg);
	
	LoginRequest req;
	req.username = forStruct["username"];
	req.password = forStruct["password"];

	return req;
}

SignupRequest& JsonRequestPacketDeserializer::deserializeSignupRequest(std::vector<unsigned char> buffer)
{
	std::string msg(buffer.begin() + 5, buffer.end());
	json forStruct = json::parse(msg);

	SignupRequest req;
	req.username = forStruct["username"];
	req.password = forStruct["password"];
	req.email = forStruct["email"];

	return req;
}

