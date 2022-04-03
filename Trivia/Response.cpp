#include "Response.h"
#include <iostream>
#include <sstream>
#include <iomanip>

#define ERR 0
#define LOGIN 1
#define SIGN 2
#define LOGOUT 3


#define MSG_LEN_SIZE 4


std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(ErrorResponse res)
{
	json response;
	response["message"] = res.message;
	return serializeResponse(response, ERR);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(SignupResponse res)
{
	json response;
	response["status"] = res.status;
	return serializeResponse(response, SIGN);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(LoginResponse res)
{
	json response;
	response["status"] = res.status;
	return serializeResponse(response, LOGIN);
}

// helper function to turn the json to vector with the msg code and msg size
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(json& response, int code)
{
	std::string jsonString = response.dump();
	int len = jsonString.length() * 4;

	std::stringstream msgLen;
	msgLen << std::setfill('0') << std::setw(MSG_LEN_SIZE) << len; //

	std::string fullMsg = char(code) + msgLen.str() + jsonString;

	return std::vector<unsigned char> (fullMsg.begin(), fullMsg.end());
}


