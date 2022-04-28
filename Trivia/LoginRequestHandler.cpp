
#include "LoginRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "Communicator.h"
#include "Response.h"

LoginRequestHandler::LoginRequestHandler()
{
}

bool LoginRequestHandler::isRequestRelevant(RequestInfo info)
// checking to see if the code matches
bool LoginRequestHandler::isRequestRelevant(RequestInfo* info)
{
    if (info->id == SIGN || info->id == LOGIN)
        return true;
    return false;
}

RequestResult* LoginRequestHandler::handleRequest(RequestInfo info)
{
    RequestResult* req = new RequestResult;
    req->buffer = info.buffer;
    
	
	switch (info.id)
	{
	case LOGIN:
	{
		req = LoginRequestHandler::login(info);
		break;
	}

	case SING: 
	{
		req = LoginRequestHandler::signup(info);
		break; 
	}

	}

    return req;
}


struct RequestResult* LoginRequestHandler::login(struct RequestInfo info)
{
	RequestResult* ret = new RequestResult;
	ret->buffer = info.buffer;

	LoginRequest req = JsonRequestPacketDeserializer::deserializeLoginRequest(info.buffer);
	if (m_loginManager.login(req.username, req.password))
	{
		ret->newHandler = m_handlerFactory.createMenuRequestHandler();
	}

	return ret;
}



struct RequestResult* LoginRequestHandler::signup(struct RequestInfo info)
{
	RequestResult* ret = new RequestResult;
	ret->buffer = info.buffer;

	SignupRequest req = JsonRequestPacketDeserializer::deserializeSignupRequest(info.buffer);
	
	if(m_loginManager.signup(req.username, req.password, req.email))
	{
		ret->newHandler = m_handlerFactory.createMenuRequestHandler();
	}

	return ret;
}