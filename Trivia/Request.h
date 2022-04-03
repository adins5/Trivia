#pragma once

#include "Communicator.h"
#include <vector>

struct LoginRequest {
	std::string username;
	std::string password;
} typedef LoginRequest;

struct SignupRequest {
	std::string username;
	std::string password;
	std::string email;
} typedef LoginRequest;

class JsonRequestPacketDeserializer {
public:
	LoginRequest deserializeLoginRequest(std::vector<unsigned char> buffer);
	SignupRequest deserializeSignupRequest(std::vector<unsigned char> buffer);

};