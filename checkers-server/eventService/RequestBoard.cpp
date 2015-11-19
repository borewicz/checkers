/*
 * RequestBoard.cpp
 *
 *  Created on: 14-11-2015
 *      Author: debian
 */

#include "RequestBoard.h"
#include <boost/lexical_cast.hpp>

RequestBoard::RequestBoard() {
}

RequestBoard::~RequestBoard() {
}

bool RequestBoard::action(Json::Value root, Server *server, Client *client) {
	return true;
}

bool RequestBoard::sendBoard(Server *server) {
	Json::Value json;
	Json::Value array(Json::arrayValue);

	boost::multi_array<char, 2> gameState { boost::extents[8][8] };
	gameState = server->game->getGameState();
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			array.append(gameState[i][j]);
		}
	}

	json["request"] = "board";
	json["board"] = array;
	json["time"] = boost::lexical_cast<std::string>(
			server->game->getActualRoundEndTime());
	json["current color"] = server->game->getCurrentMovementColor();

	for (auto const& iterator : server->clients->getBlackClients()) {
		if (iterator.second->getIsConnected()) {
			sendResponse(json, iterator.second);
		}
	}
	for (auto const& iterator : server->clients->getWhiteClients()) {
		if (iterator.second->getIsConnected()) {
			sendResponse(json, iterator.second);
		}
	}
	return true;
}

