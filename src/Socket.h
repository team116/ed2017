/*
 * socket.h
 *
 *  Created on: Feb 15, 2017
 *      Author: attar
 */

#ifndef SRC_SOCKET_H_
#define SRC_SOCKET_H_

class Socket {
public:
	Socket();
	int process();
	virtual ~Socket();
private:
	 int client;

};

#endif /* SRC_SOCKET_H_ */
