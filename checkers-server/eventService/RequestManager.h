/*
 * RequestManager.h
 *
 *  Created on: 09-11-2015
 *      Author: debian
 */

#ifndef EVENTSERVICE_REQUESTMANAGER_H_
#define EVENTSERVICE_REQUESTMANAGER_H_

#include <map>
#include <string.h>
#include "RequestService.h"
#include "../jsonParser/json/json.h"
#include "../game/Server.h"
#include "../game/Client.h"

using namespace std;

class RequestManager {
private:
	map<string, RequestService*> requestServices;
	Json::Value root;
	Json::Reader reader;

public:
	RequestManager();
	virtual ~RequestManager();
	int requestReaction(string request, Server *server, Client *client);
};

#endif /* EVENTSERVICE_REQUESTMANAGER_H_ */
