/*
 * ServidorEx.cpp
 *
 *  Created on: May 17, 2009
 *      Author: mmmary
 */
#include <iostream>
#include "server_ServidorEx.h"
#include "server_Cliente.h"
#define MAXCANTINTENTOS 20

ServidorEx::ServidorEx(Servidor* servidor) {
	this->servidor = servidor;
	socket = NULL;
	int cantidadIntentos = 0;
	while ((socket==NULL) && cantidadIntentos < MAXCANTINTENTOS) {
		this->socket = new MSocket(servidor->getPuerto(), servidor->getCantClientes());
cantidadIntentos++;
		}

	int retorno = this->socket->listen(servidor->getPuerto(), servidor->getCantClientes());
	isValido = (retorno == 0);
}

bool ServidorEx::getIsValido(){
	return isValido;
}
void* ServidorEx::run(){
		this->servidor->setEstado(true);
		while (this->servidor->getEstado()) {
			MSocket* socketCliente = this->socket->accept();
			if (socketCliente != NULL) {
				/*hay un cliente*/
				Cliente* cliente = new Cliente(socketCliente, this->servidor);
				cliente->execute();
			}
		}
		return NULL;
}

void ServidorEx::dejarDeEscuchar(){
	socket->shutdown();
	join();
}

ServidorEx::~ServidorEx() {
	delete this->socket;
}
