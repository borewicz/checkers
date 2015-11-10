/*
 * TCPClientAcceptor.h
 *
 *  Created on: 07-11-2015
 *      Author: Sebastian
 */

#ifndef NETWORK_TCPCLIENTACCEPTOR_H_
#define NETWORK_TCPCLIENTACCEPTOR_H_

#include "TCPClientConnection.h"
#include <iostream>

using namespace std;

class TCPClientAcceptor {
private:
	int sock;
	string host;
	int port;
	bool isListening;

public:
	TCPClientAcceptor(int server_port, const char* address);
	virtual ~TCPClientAcceptor();

	bool start();
	TCPClientConnection* acceptConnection();
};

#endif /* NETWORK_TCPCLIENTACCEPTOR_H_ */
