/*
 * requestService.cpp
 *
 *  Created on: 09-11-2015
 *      Author: debian
 */

#include "RequestService.h"

RequestService::RequestService() {
}

RequestService::~RequestService() {
}

bool RequestService::sendResponse(Json::Value root, Client *client) {

	string response = writer.write(root);
	int size = response.size();
	char buffer[size];
	strcpy(buffer, response.c_str());
	int err = client->getNetwork()->send(buffer, size);
	if (err < 0) {
		cout << "error in sending response to client";
	}
	return true;
}

Json::Value RequestService::shortJson(string key, string value) {
	Json::Value json;
	json[key] = value;
	return json;
}

