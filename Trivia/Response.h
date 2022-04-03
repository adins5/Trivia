#pragma once

#include "Communicator.h"
#include <vector>
#include "json.hpp"

using json = nlohmann::json;

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
