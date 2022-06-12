#pragma once
#include "IRequestHandler.h"
#include "LoggedUser.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
#include "Communicator.h"


class RequestHandlerFactory;

class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler(LoggedUser user, roomManager& roomManager, StatisticsManager& statisticsManager, RequestHandlerFactory& handelFactory) : m_user(user), m_roomManager(roomManager), m_statisticsManager(statisticsManager), m_handelFactory(handelFactory) {}
	~MenuRequestHandler() = default;

	bool isRequestRelevant(RequestInfo info) override;
	RequestResult* handleRequest(RequestInfo info, SOCKET soc) override;
	
	RequestResult* signout(RequestInfo info, SOCKET soc);
	RequestResult* getRooms(RequestInfo info, SOCKET soc);
	RequestResult* getPlayersInRoom(RequestInfo info, SOCKET soc);
	RequestResult* getPersonalStats(RequestInfo info, SOCKET soc);
	RequestResult* getHighScore(RequestInfo info, SOCKET soc);
	RequestResult* joinRoom(RequestInfo info, SOCKET soc);
	RequestResult* createRoom(RequestInfo info, SOCKET soc);

private:
	LoggedUser m_user;
	roomManager& m_roomManager;
	StatisticsManager& m_statisticsManager;
	RequestHandlerFactory& m_handelFactory;
};
