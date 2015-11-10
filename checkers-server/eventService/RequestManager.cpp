/*
 * RequestManager.cpp
 *
 *  Created on: 09-11-2015
 *      Author: debian
 */

#include "RequestManager.h"
#include "RequestService.h"
#include "RequestError.h"
#include "../jsonParser/json/json.h"

using namespace std;
RequestManager::RequestManager() {
	RequestService *requestError = new RequestError();
	requestServices["error"] = requestError;
}

RequestManager::~RequestManager() {
	for (map<string, RequestService*>::iterator it = requestServices.begin();
			it != requestServices.end(); ++it) {
		delete (it->second);
	}
}

bool RequestManager::requestReaction(string request, Clients *clients,
		Game *game) {
	bool err = reader.parse(request, root);
	if (!err) {
		std::cout << "Failed to parse request "
				<< reader.getFormattedErrorMessages();
		return false;
	}

	std::string requestType = root.get("request", "error").asString();

	err = requestServices[requestType]->action(request, clients, game);

	return err;
}

