#include "Response.h"
#include <iostream>
#include <sstream>
#include <iomanip>


#define MSG_LEN_SIZE 4


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

// helper function to turn the json to vector with the msg code and msg size
std::string JsonResponsePacketSerializer::serializeResponse(json& response, int code)
{
	std::string jsonString = response.dump();
	int len = jsonString.length() * 4;

	std::stringstream msgLen;
	msgLen << std::setfill('0') << std::setw(MSG_LEN_SIZE) << len; //

	std::string fullMsg = char(code) + msgLen.str() + jsonString;

	return fullMsg;
}


