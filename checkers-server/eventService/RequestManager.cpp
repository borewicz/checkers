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
	for (auto const& iterator : requestServices) {
		delete (iterator.second);
	}
}

int RequestManager::requestReaction(string request, Server *server,
		Client *client) {
	int result = -1; //parser error reaction
	bool err = reader.parse(request, root);
	if (!err) {
		std::cout << "Failed to parse request "
				<< reader.getFormattedErrorMessages();
		requestServices["error"]->action(root, server, client);
		return result;
	}
	string requestType;
	if (!root.isMember("request")) {
		requestType = "error";
		result = -2; //no request field
	} else {
		requestType = root.get("request", "error").asString();
		//if undefined request type
		if (requestServices.find(requestType) == requestServices.end()) {
			requestType = "error";
		}
		if ((requestType == "movement") || (requestType == "connect")
				|| (requestType == "disconnect")) {
			result = 2; //request which wake up game
		} else {
			result = 1; //other request
		}
		err = requestServices[requestType]->action(root, server, client);
		if (!err) {
			result = 0;
		}
	}
	return result;
}

