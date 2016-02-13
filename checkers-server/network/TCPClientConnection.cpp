/*
 * TCPClientConnection.cpp
 *
 *  Created on: 07-11-2015
 *      Author: Sebastian
 */

#include "TCPClientConnection.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdexcept>
#include <fcntl.h>

TCPClientConnection::TCPClientConnection(int client_sock,
		struct sockaddr_in* address) {
	sock = client_sock;
	char ip[50];
	inet_ntop(PF_INET, (struct in_addr*) &(address->sin_addr.s_addr), ip,
			sizeof(ip) - 1);
	host = ip;
	port = ntohs(address->sin_port);
}

TCPClientConnection::TCPClientConnection() {
	sock = 0;
	host = "";
	port = 0;
}

TCPClientConnection::TCPClientConnection(const TCPClientConnection& client) {
	sock = client.sock;
	host = client.host;
	port = client.port;
}

TCPClientConnection::~TCPClientConnection() {
	close(sock);
}

int TCPClientConnection::receive(char* buffer, size_t len) {
	char dataSize[4];
	int receiveSize = recv(sock, dataSize, 4, MSG_WAITALL);
	if (receiveSize < 0) {
		return -1;
	}
	if (receiveSize == 0) {
			return 0;
	}
	size_t size;
	try {
		size = std::stoi(dataSize);
	} catch (std::invalid_argument& e) {
		printf("invalid argument\n");
		read(sock, buffer, len);
		return -2;
	}
	if (size > len) {
		printf("too big message \n");
		read(sock, buffer, len);
		return -2;
	}
	receiveSize = recv(sock, buffer, size, MSG_WAITALL);
	return receiveSize;
}

int TCPClientConnection::send(char* buffer, size_t len) {
//	printf(buffer);
	return write(sock, buffer, len);
}

string TCPClientConnection::getHost() {
	return host;
}

int TCPClientConnection::getPort() {
	return port;
}

int TCPClientConnection::getSock() {
	return sock;
}
