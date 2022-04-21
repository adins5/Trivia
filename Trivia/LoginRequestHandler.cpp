#include "LoginRequestHandler.h"

LoginRequestHandler::LoginRequestHandler()
{
}

bool LoginRequestHandler::isRequestRelevant(RequestInfo info)
{
    if (info.id == SIGN || info.id == LOGIN)
        return true;
    return false;
}

RequestResult* LoginRequestHandler::handleRequest(RequestInfo info)
{
    RequestResult* req = new RequestResult;
    req->buffer = info.buffer;
    //req->newHandler = LoginRequestHandler();

    return req;
}
