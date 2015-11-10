/*
 * RequestError.h
 *
 *  Created on: 09-11-2015
 *      Author: debian
 */

#ifndef EVENTSERVICE_REQUESTERROR_H_
#define EVENTSERVICE_REQUESTERROR_H_

#include "RequestService.h"

class RequestError : public RequestService{
public:
	RequestError();
	virtual ~RequestError();

	bool action(string request, Clients *clients, Game *game);
};

#endif /* EVENTSERVICE_REQUESTERROR_H_ */
