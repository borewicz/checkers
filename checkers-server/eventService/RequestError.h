/*
 * RequestError.h
 *
 *  Created on: 09-11-2015
 *      Author: debian
 */

#ifndef EVENTSERVICE_REQUESTERROR_H_
#define EVENTSERVICE_REQUESTERROR_H_

#include "RequestService.h"
#include "../game/Server.h"
#include "../game/Client.h"

class RequestError : public RequestService{
public:
	RequestError();
	virtual ~RequestError();

	bool action(Json::Value root, Server *server, Client *client);
};

#endif /* EVENTSERVICE_REQUESTERROR_H_ */
