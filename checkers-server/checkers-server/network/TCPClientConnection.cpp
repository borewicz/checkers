/*
 * TCPClientConnection.cpp
 *
 *  Created on: 07-11-2015
 *      Author: debian
 */

#include "TCPClientConnection.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

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

ssize_t TCPClientConnection::receive(char* buffer, size_t len) {
	return read(sock, buffer, len);
}

ssize_t TCPClientConnection::send(char* buffer, size_t len) {
	return write(sock, buffer, len);
}

string TCPClientConnection::getHost() {
	return host;
}

int TCPClientConnection::getPort() {
	return port;
}
