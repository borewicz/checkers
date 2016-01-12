/*
 * RequestError.cpp
 *
 *  Created on: 09-11-2015
 *      Author: debian
 */

#include "RequestError.h"

#include <iostream>

RequestError::RequestError() {
}

RequestError::~RequestError() {
}

bool RequestError::action(Json::Value root, Server *server, Client *client){
	cout<<"Wrong request"<<endl;
	sendResponse(shortJson("status", "request error"), client);
	return true;
}


