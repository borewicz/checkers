/*
 * RequestMessage.h
 *
 *  Created on: 12-11-2015
 *      Author: debian
 */

#ifndef EVENTSERVICE_REQUESTMESSAGE_H_
#define EVENTSERVICE_REQUESTMESSAGE_H_

#include "RequestService.h"
#include "../game/Client.h"
#include "../game/Server.h"

class RequestMessage: public RequestService {
public:
	RequestMessage();
	virtual ~RequestMessage();

	bool action(Json::Value root, Server *server, Client *client);
};

#endif /* EVENTSERVICE_REQUESTMESSAGE_H_ */
