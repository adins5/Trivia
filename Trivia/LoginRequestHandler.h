#pragma once

#include "IRequestHandler.h"
#include "LoginManager.h"
#include "Communicator.h"

//class Communicator;
class RequestHandlerFactory;
class Communicator;

class LoginRequestHandler : public IRequestHandler {

public:
	LoginRequestHandler(LoginManager& loginManager, RequestHandlerFactory& handlerFactory) : m_loginManager(loginManager), m_handlerFactory(handlerFactory) {}
	~LoginRequestHandler() = default;

	bool isRequestRelevant(struct RequestInfo info) override;
	struct RequestResult* handleRequest(struct RequestInfo info) override;

	struct RequestResult* login(struct RequestInfo info);
	struct RequestResult* signup(struct RequestInfo info);

private:
	LoginManager& m_loginManager;
	RequestHandlerFactory& m_handlerFactory;
};