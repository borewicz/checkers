/*
 * RequestBoard.h
 *
 *  Created on: 14-11-2015
 *      Author: debian
 */

#ifndef EVENTSERVICE_REQUESTBOARD_H_
#define EVENTSERVICE_REQUESTBOARD_H_

#include "RequestService.h"

class RequestBoard: public RequestService {
public:
	RequestBoard();
	virtual ~RequestBoard();

	bool action(Json::Value root, Server *server, Client *client);bool sendBoard(
			Server *server);bool gameOver(Server *server);bool gameOver(
			Server *server, string winner);
private:
	bool sendGameOverRequest(Server *server, string winner);
	bool sendRequests(Server *server, Json::Value json);
};

#endif /* EVENTSERVICE_REQUESTBOARD_H_ */
