/*
 * TCPClientAcceptor.cpp
 *
 *  Created on: 07-11-2015
 *      Author: Sebastian
 */

#include "TCPClientAcceptor.h"

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

TCPClientAcceptor::TCPClientAcceptor(int serverPort, const char* address) {
	port = serverPort;
	sock = 0;
	isListening = false;
	host = address;
}

TCPClientAcceptor::~TCPClientAcceptor() {
	if (sock > 0) {
		close(sock);
	}
}

int TCPClientAcceptor::start() {
	if (isListening == true) {
		printf("Server is already listening");
		return 0;
	}

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		printf("Could not create socket");
		return 0;
	}

	struct sockaddr_in address;

	address.sin_family = PF_INET;
	address.sin_port = htons(port);
	if (host.size() > 0) {
		inet_pton(PF_INET, host.c_str(), &(address.sin_addr));
	} else {
		address.sin_addr.s_addr = INADDR_ANY;
	}

	int option = 1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

	int err = bind(sock, (struct sockaddr*) &address, sizeof(address));
	if (err != 0) {
		printf("bind() error");
		return err;
	}
	err = listen(sock, 5);
	if (err != 0) {
		printf("listen() error");
		return err;
	}
	isListening = true;
	return 0;
}

TCPClientConnection* TCPClientAcceptor::acceptConnection() {
	if (isListening == false) {
		return NULL;
	}

	struct sockaddr_in address;
	socklen_t length = sizeof(address);
	memset(&address, 0, sizeof(address));
	int clientSocket = accept(sock, (struct sockaddr*) &address, &length);
	if (clientSocket < 0) {
		printf("accept() error");
		return NULL;
	}
	return new TCPClientConnection(clientSocket, &address);
}

