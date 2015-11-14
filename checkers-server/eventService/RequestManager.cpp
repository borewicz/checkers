/*
 * RequestManager.cpp
 *
 *  Created on: 09-11-2015
 *      Author: debian
 */

#include "RequestManager.h"
#include "RequestService.h"

#include "RequestError.h"
#include "RequestConnect.h"
#include "RequestMessage.h"
#include "RequestDisconnect.h"
#include "RequestMovement.h"

#include "../jsonParser/json/json.h"
#include "../game/Server.h"

using namespace std;
RequestManager::RequestManager() {
	RequestService *requestError = new RequestError();
	requestServices["error"] = requestError;

	RequestService *requestConnect = new RequestConnect();
	requestServices["connect"] = requestConnect;

	RequestService *requestMessage = new RequestMessage();
	requestServices["message"] = requestMessage;

	RequestService *requestDisconnect = new RequestDisconnect();
	requestServices["disconnect"] = requestDisconnect;

	RequestService *requestMovement = new RequestMovement();
	requestServices["movement"] = requestMovement;
}

RequestManager::~RequestManager() {
	for (map<string, RequestService*>::iterator it = requestServices.begin();
			it != requestServices.end(); ++it) {
		delete (it->second);
	}
}

bool RequestManager::requestReaction(string request, Server *server,
		Client *client) {
	bool err = reader.parse(request, root);
	if (!err) {
		std::cout << "Failed to parse request "
				<< reader.getFormattedErrorMessages();
		return false;
	}
	std::string requestType;
	if (root.isMember("request")) {
		requestType = root.get("request", "error").asString();
		if (requestServices.find(requestType) == requestServices.end()) {
			requestType = "error";
		}
	} else {
		requestType = "error";
	}
	err = requestServices[requestType]->action(root, server, client);
	return err;
}

