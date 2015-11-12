/*
 * RequestConnect.h
 *
 *  Created on: 12-11-2015
 *      Author: debian
 */

#ifndef EVENTSERVICE_REQUESTCONNECT_H_
#define EVENTSERVICE_REQUESTCONNECT_H_

#include "RequestService.h"
#include "../game/Client.h"
#include "../game/Server.h"

class RequestConnect : public RequestService {
public:
	RequestConnect();
	virtual ~RequestConnect();

	bool action(Json::Value root, Server *server, Client *client);

private:
	Json::Value responseJson(Clients *clients, int id);
};

#endif /* EVENTSERVICE_REQUESTCONNECT_H_ */
