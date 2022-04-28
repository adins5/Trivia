
#include "LoginRequestHandler.h"
#include "Response.h"

LoginRequestHandler::LoginRequestHandler()
{
}

// checking to see if the code matches
bool LoginRequestHandler::isRequestRelevant(RequestInfo* info)
{
    if (info->id == SIGN || info->id == LOGIN)
        return true;
    return false;
}

RequestResult* LoginRequestHandler::handleRequest(RequestInfo* info, SOCKET soc)
{
    RequestResult* ret = new RequestResult;
    ret->buffer = info->buffer;
	switch (info->id)
	{
	case LOGIN: {
		LoginRequest logReq = JsonRequestPacketDeserializer::deserializeLoginRequest(info->buffer);
		LoginResponse* res = new LoginResponse;
		res->status = 1;
		MessageHandler::sendMsg(JsonResponsePacketSerializer::serializeResponse(*res), soc);
		break; }

	case SING: {
		SignupRequest signReq = JsonRequestPacketDeserializer::deserializeSignupRequest(info->buffer);
		SignupResponse* res = new SignupResponse;
		res->status = 2;
		MessageHandler::sendMsg(JsonResponsePacketSerializer::serializeResponse(*res), soc);
		break; }
	}

	ret->newHandler = nullptr; //

    return ret;
}
