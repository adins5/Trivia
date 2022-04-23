#include "RequestHandlerFactory.h"
#include "LoginRequestHandler.h"


LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler(m_loginManager, *this);
}


MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler()
{
	return new MenuRequestHandler;
}