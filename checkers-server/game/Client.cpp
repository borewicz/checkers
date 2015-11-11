/*
 * Client.cpp
 *
 *  Created on: 09-11-2015
 *      Author: debian
 */

#include "Client.h"

Client::Client(TCPClientConnection *network, char color, string nick) {
	this->network = network;
	this->color = color;
	this->nick = nick;
	this->ID = network->getSock();
	this->isConnected = false;
	this->threadEnabled = true;
}

Client::Client(TCPClientConnection *network) {
	string nick = "";
	this->color = ' ';
	this->network = network;
	this->ID = network->getSock();
	this->isConnected = false;
	this->threadEnabled = true;
}

Client::~Client() {
	delete (network);
}

void Client::terminateThread() {
	threadEnabled = false;
}

bool Client::getThreadEnabled() {
	return threadEnabled;
}

char Client::getColor() {
	return color;
}

int Client::getID() {
	return ID;
}

string Client::getNick() {
	return nick;
}

void Client::setColor(char color) {
	this->color = color;
}

void Client::setNick(string nick) {
	this->nick = nick;
}

bool Client::getIsConnected() {
	return isConnected;
}

void Client::setIsConnected(bool connected) {
	this->isConnected = connected;
}

TCPClientConnection* Client::getNetwork() {
	return network;
}
