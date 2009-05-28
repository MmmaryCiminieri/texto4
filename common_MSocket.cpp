/*
 * MSocket.cpp
 *
 *  Created on: Apr 24, 2009
 *      Author: mmmary
 */

#include "common_MSocket.h"
#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <cstring>
#include <iostream>
#include <stdlib.h>

MSocket::MSocket(int fd) {
	this->fd = fd;
	if (fd == -1) {
		this->valid = false;
		return;
	}
	this->dest_addr.sin_family = AF_INET;
memset(this->dest_addr.sin_zero, '\0', sizeof(this->dest_addr.sin_zero));
	this->valid = true;
}

MSocket::MSocket() {
	this->fd = -1;
		this->fd = socket(PF_INET, SOCK_STREAM, 0);

	if (fd == -1) {
		this->valid = false;
	} else {
		this->valid = true;
	}
}

MSocket::MSocket(int puerto, int cantClientes) {
this->fd = socket(PF_INET, SOCK_STREAM, 0);

		this->dest_addr.sin_family = AF_INET;
	this->dest_addr.sin_port = htons(puerto);
	this->dest_addr.sin_addr.s_addr = INADDR_ANY;
	memset(this->dest_addr.sin_zero, '\0', sizeof(this->dest_addr.sin_zero));
	this->valid = true;

}

int MSocket::connect(const char* ip, const char* port) {

	if (this->valid) {

				hostent* h;
				struct sockaddr_in destino;
				destino.sin_family = AF_INET;
				destino.sin_port = htons(atoi(port));

				if ((h= gethostbyname(ip))) {

					destino.sin_addr.s_addr = ((struct in_addr*) (h->h_addr))->s_addr;

					return ::connect(fd, (struct sockaddr *) &destino, sizeof(destino));
				}
			}
			return -1;

}

int MSocket::shutdown(){

	return ::shutdown(fd, SHUT_RDWR);
}
int MSocket::listen(unsigned int port, unsigned int cantClientes) {

	if (this->isValid()) {
		int aux = bind(this->fd, (struct sockaddr*) (&(this->dest_addr)),
				sizeof(this->dest_addr));

		if (aux == -1) {
			return -1;
		}
		int aux2 = ::listen(this->fd, cantClientes);

		if (aux2 != -1) {
			return 0;
		}
	}

	return -1;
}

int MSocket::send(const std::string& stream) {
	int retorno = 0;
	int size= stream.size();
	int cantEnv = 0;
	if (isValid()) {

		while (cantEnv < size) {
			if ((retorno = ::send(this->fd, stream.c_str(), size, 0)) != -1) {
				cantEnv += retorno;

			} else {
				return -1;
			}
		}
		return 0;
	}
	return -1;
}

void MSocket::close() {
	std::cout << "MSocket::close() para " << fd << std::endl;
if(fd != -1){
	::close(fd);
	fd = -1;
}
}
int MSocket::recieve(char* buffer, unsigned int size) {

	int retorno = ::recv(this->fd, buffer, size, 0);

	//TODO borrar esto
	if (retorno < 0) {
		std::cout << "el recv no anda " << std::endl;
	}

	return retorno;
}

MSocket* MSocket::accept() {

	int new_fd = ::accept(this->fd, NULL, NULL);
	if (new_fd == -1) {
		return NULL;
	}
	return new MSocket(new_fd);
}

bool MSocket::isValid() {
	return this->valid;
}

MSocket::~MSocket() {
	close();
}
