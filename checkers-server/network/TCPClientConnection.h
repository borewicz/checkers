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

	int receive(char* buffer, size_t len);
	int send(char* buffer, size_t len);

    string getHost();
    int getPort();
    int getSock();

private:
	TCPClientConnection(int sock, struct sockaddr_in *address);
	TCPClientConnection();
	TCPClientConnection(const TCPClientConnection& client);
};

#endif /* NETWORK_TCPCLIENTCONNECTION_H_ */
