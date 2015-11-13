/*
 * requestService.h
 *
 *  Created on: 09-11-2015
 *      Author: debian
 */

#ifndef EVENTSERVICE_REQUESTSERVICE_H_
#define EVENTSERVICE_REQUESTSERVICE_H_

#include "../jsonParser/json/json.h"
#include "../game/Server.h"
#include "../game/Client.h"


class RequestService {
protected:
	Json::Reader reader;
	Json::StyledWriter writer;

public:
	RequestService();
	virtual ~RequestService();

	virtual bool action(Json::Value root, Server *server, Client *client) = 0;
	Json::Value shortJson(string key, string value);
	bool sendResponse(Json::Value root, Client *client);

};

#endif /* EVENTSERVICE_REQUESTSERVICE_H_ */
