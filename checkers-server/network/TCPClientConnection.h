/*
 * TCPClientConnection.h
 *
 *  Created on: 07-11-2015
 *      Author: Sebastian
 */

#ifndef NETWORK_TCPCLIENTCONNECTION_H_
#define NETWORK_TCPCLIENTCONNECTION_H_

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>


using namespace std;

class TCPClientConnection {
private:
	int sock;
	string host;
	int port;

public:
	friend class TCPClientAcceptor;

	virtual ~TCPClientConnection();

	ssize_t receive(char* buffer, size_t len);
	ssize_t send(char* buffer, size_t len);

    string getHost();
    int getPort();

private:
	TCPClientConnection(int sock, struct sockaddr_in *address);
	TCPClientConnection();
	TCPClientConnection(const TCPClientConnection& client);
};

#endif /* NETWORK_TCPCLIENTCONNECTION_H_ */
