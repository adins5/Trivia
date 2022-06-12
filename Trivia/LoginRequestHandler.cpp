#include "LoginRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "Response.h"



bool LoginRequestHandler::isRequestRelevant(RequestInfo info)
{
    if (info.id == SIGN || info.id == LOGIN)
        return true;
    return false;
}

RequestResult* LoginRequestHandler::handleRequest(RequestInfo info, SOCKET soc)
{
    RequestResult* req = new RequestResult;
    req->buffer = info.buffer;
    
	
	switch (info.id)
	{
	case LOGIN:
	{
		req = LoginRequestHandler::login(info, soc);
		break;
	}

	case SING: 
	{
		req = LoginRequestHandler::signup(info, soc);
		break; 
	}

	}

    return req;
}


struct RequestResult* LoginRequestHandler::login(struct RequestInfo info, SOCKET soc)
{
	LoginResponse* res = new LoginResponse;
	
	RequestResult* ret = new RequestResult;
	ret->buffer = info.buffer;
	
	LoginRequest* req = JsonRequestPacketDeserializer::deserializeLoginRequest(info.buffer);
	if (!m_loginManager.login(req->username, req->password))
	{
		res->status = 0;
		ret->newHandler = m_handlerFactory.createLoginRequestHandler();
		MessageHandler::sendMsg(JsonResponsePacketSerializer::serializeResponse(*res), soc);
		return ret;
	}

	LoggedUser user(req->username);
	ret->newHandler = (IRequestHandler*)m_handlerFactory.createMenuRequestHandler(user);
	res->status = 1;
	MessageHandler::sendMsg(JsonResponsePacketSerializer::serializeResponse(*res), soc);

	return ret;
}



struct RequestResult* LoginRequestHandler::signup(struct RequestInfo info, SOCKET soc)
{
	SignupResponse* res = new SignupResponse;

	RequestResult* ret = new RequestResult;
	ret->buffer = info.buffer;

	SignupRequest* req = JsonRequestPacketDeserializer::deserializeSignupRequest(info.buffer);
	if (!m_loginManager.signup(req->username, req->password, req->email))
	{
		res->status = 0;
		ret->newHandler = m_handlerFactory.createLoginRequestHandler();
		MessageHandler::sendMsg(JsonResponsePacketSerializer::serializeResponse(*res), soc);
		return ret;
	}

	LoggedUser user(req->username);
	ret->newHandler = (IRequestHandler*)m_handlerFactory.createMenuRequestHandler(user);

	res->status = 1;
	MessageHandler::sendMsg(JsonResponsePacketSerializer::serializeResponse(*res), soc);

	return ret;
}