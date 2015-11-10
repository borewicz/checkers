/*
 * requestService.h
 *
 *  Created on: 09-11-2015
 *      Author: debian
 */

#ifndef EVENTSERVICE_REQUESTSERVICE_H_
#define EVENTSERVICE_REQUESTSERVICE_H_

#include "../jsonParser/json/json.h"
#include "../game/Clients.h"
#include "../game/Game.h"

class RequestService {
private:
	Json::Value root;
	Json::Reader reader;

public:
	RequestService();
	virtual ~RequestService();

	virtual bool action(string request, Clients *clients, Game *game) = 0;
};

#endif /* EVENTSERVICE_REQUESTSERVICE_H_ */
