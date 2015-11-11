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

class RequestError : public RequestService{
public:
	RequestError();
	virtual ~RequestError();

	bool action(string request, Server *server);
};

#endif /* EVENTSERVICE_REQUESTERROR_H_ */
