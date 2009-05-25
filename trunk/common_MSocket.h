/*
 * MSocket.h
 *
 *  Created on: Apr 24, 2009
 *      Author: mmmary
 */

/* Representacion de un Socket
 * */
#ifndef MSOCKET_H_
#define MSOCKET_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>

class MSocket {
private:
	int fd;
	sockaddr_in dest_addr;
	bool valid;

	MSocket(int fd);
	MSocket(const MSocket& socket);


public:

	MSocket();
	MSocket(int puerto, int cantClientes);

	int connect(const char* ip, const char* port);

	int listen(unsigned int port, unsigned int nro_cliente_espera);
	int send(std::string stream, unsigned int size );
	int recieve(char*  buffer, unsigned int size);
	MSocket* accept();
	void close();

	bool isValid();
	virtual ~MSocket();
};

#endif /* MSOCKET_H_ */
