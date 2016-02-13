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
	Json::Value json;
	json = createBoardJson(server);
	sendResponse(json, client);
	return true;
}

bool RequestBoard::sendBoard(Server *server) {
	Json::Value json;
	json = createBoardJson(server);
	return sendRequests(server, json);
}

bool RequestBoard::gameOver(Server *server) {
	if (server->game->isGameEnd()) {
		string result = server->game->getWinnerColor();
		if ((result == "white") || (result == "black")) {
			return sendGameOverRequest(server, result);
		}
	}
	return false;
}

bool RequestBoard::gameOver(Server *server, string winner) {
	return sendGameOverRequest(server, winner);
}

bool RequestBoard::sendGameOverRequest(Server *server, string winner) {
	Json::Value json;
	json["request"] = "game_over";
	json["winner"] = winner;
	return sendRequests(server, json);
}

bool RequestBoard::sendRequests(Server *server, Json::Value json) {
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

Json::Value RequestBoard::createBoardJson(Server *server) {
	Json::Value json;
	Json::Value array;

	boost::multi_array<char, 2> gameState { boost::extents[8][8] };
	gameState = server->game->getGameState();
	for (int i = 7; i >= 0; i--) {
		Json::Value array2;
		for (int j = 0; j < 8; j++) {
			;
			string text = "";
			text += gameState[j][i];
			array2.append(text);
		}
		array.append(array2);
	}

	json["request"] = "board";
	json["board"] = array;
	json["time"] = boost::lexical_cast<std::string>(
			server->game->getActualRoundEndTime());
	json["current color"] = server->game->getCurrentMovementColor();
	return json;
}
