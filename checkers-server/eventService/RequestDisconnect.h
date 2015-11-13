/*
 * RequestDisconnect.h
 *
 *  Created on: 13-11-2015
 *      Author: debian
 */

#ifndef EVENTSERVICE_REQUESTDISCONNECT_H_
#define EVENTSERVICE_REQUESTDISCONNECT_H_

#include "RequestService.h"

class RequestDisconnect: public RequestService {
public:
	RequestDisconnect();
	virtual ~RequestDisconnect();

	bool action(Json::Value root, Server *server, Client *client);
};

#endif /* EVENTSERVICE_REQUESTDISCONNECT_H_ */
