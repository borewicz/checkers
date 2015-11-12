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
	char buffer[BLOCK_SIZE];
	string response = writer.write(root);
	strcpy(buffer, response.c_str());
	int err = client->getNetwork()->send(buffer, BLOCK_SIZE);
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

