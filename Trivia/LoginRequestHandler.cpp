#include "LoginRequestHandler.h"

LoginRequestHandler::LoginRequestHandler()
{
}

bool LoginRequestHandler::isRequestRelevant(RequestInfo info)
{
    return false;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo info)
{
    RequestResult req;
    req.buffer = info.buffer;

    if (info.id == LOGIN)
    {

    }

    if (info.id == SING)
    {

    }

    return req;
}

LoginRequestHandler::~LoginRequestHandler()
{
}
