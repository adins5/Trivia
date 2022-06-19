#include "RequestHandlerFactory.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler(m_loginManager, *this);
}


MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(LoggedUser user)
{
	return new MenuRequestHandler(user, m_roomManager, m_statisticsManager, *this);
}



RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(LoggedUser user, int roomId)
{
	return new RoomAdminRequestHandler(m_roomManager.getRoom(roomId), user, m_roomManager, *this)	;

}


RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler(LoggedUser user, int roomId)
{
	return new RoomMemberRequestHandler(m_roomManager.getRoom(roomId), user, m_roomManager, *this);

}

std::vector<std::string> RequestHandlerFactory::UserNames()
{
	return m_database->getUserNames();
}
