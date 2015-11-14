/*
 * RequestMovement.h
 *
 *  Created on: 13-11-2015
 *      Author: debian
 */

#ifndef EVENTSERVICE_REQUESTMOVEMENT_H_
#define EVENTSERVICE_REQUESTMOVEMENT_H_

#include "RequestService.h"

class RequestMovement: public RequestService {
public:
	RequestMovement();
	virtual ~RequestMovement();

	bool action(Json::Value root, Server *server, Client *client);
};

#endif /* EVENTSERVICE_REQUESTMOVEMENT_H_ */
