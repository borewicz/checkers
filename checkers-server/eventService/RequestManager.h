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

using namespace std;

class RequestManager {
private:
	map<string, RequestService*> requestsServices;
public:

	RequestManager();
	virtual ~RequestManager();
};

#endif /* EVENTSERVICE_REQUESTMANAGER_H_ */
