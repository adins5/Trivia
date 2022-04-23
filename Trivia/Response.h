#pragma once

#include <vector>
#include "json.hpp"
using json = nlohmann::json;

#define ERR 0
#define LOGIN 1
#define SIGN 2
#define LOGOUT 3

struct ErrorResponse {
	std::string message;
} typedef ErrorResponse;

struct LoginResponse {
	unsigned int status;
} typedef LoginResponse;

struct SignupResponse {
	unsigned int status;
} typedef SignupResponse;


class JsonResponsePacketSerializer {
public:
	static std::vector<unsigned char> serializeResponse(ErrorResponse res);
	static std::vector<unsigned char> serializeResponse(SignupResponse res);
	static std::vector<unsigned char> serializeResponse(LoginResponse res);

private:
	static std::vector<unsigned char> serializeResponse(json& response, int code);

};
