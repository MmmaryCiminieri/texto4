/*
 * MSocket.h
 *
 *  Created on: Apr 24, 2009
 *      Author: mmmary
 */

/* Encapsulamiento de un Socket
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
	bool operator==(const MSocket& otro)const;


public:

	MSocket();
	MSocket(int puerto, int cantClientes);

	/*se conecta a un ip en el puerto port. retorna: 0 si ok, -1 si no.*/
	int connect(const char* ip, const char* port);

	/*escucha en un puerto. retorna: 0 si ok, -1 si no.*/
	int listen(unsigned int port, unsigned int nro_cliente_espera);

	/*Si el socket esta conectado intenta eviar el stream retorna: 0 si puede, -1 si no*/
	int send(const std::string& stream);

	/*BLOQUEANTE, recibe algo que guarda en buffer de tamanio size.
	 * retorna -1 si la conxion ha sido cerrada desde el otro lado
	 * y si no retorna cuanto ha rebido en bytes*/
	int recieve(char*  buffer, unsigned int size);

	/*BLOQUEANTE acepto un connect() que me hicieron desde otro lado y creo un socket
	 * para atenderlo */
	MSocket* accept();

	/*cierra la conexion*/
	void close();

	bool isValid();
	virtual ~MSocket();
};

#endif /* MSOCKET_H_ */
