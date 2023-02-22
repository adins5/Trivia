#pragma once

#include "IRequestHandler.h"
#include "LoginManager.h"


class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler {

public:
	LoginRequestHandler(LoginManager& loginManager, RequestHandlerFactory& handlerFactory) : m_loginManager(loginManager), m_handlerFactory(handlerFactory) {}
	~LoginRequestHandler() = default;

	virtual bool isRequestRelevant(struct RequestInfo info) override;
	virtual struct RequestResult* handleRequest(struct RequestInfo info, SOCKET soc) override;

	struct RequestResult* login(struct RequestInfo info, SOCKET soc);
	struct RequestResult* signup(struct RequestInfo info, SOCKET soc);

private:
	LoginManager& m_loginManager;
	RequestHandlerFactory& m_handlerFactory;
};