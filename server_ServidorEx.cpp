/*
 * ServidorEx.cpp
 *
 *  Created on: May 17, 2009
 *      Author: mmmary
 */
#include <iostream>
#include "server_ServidorEx.h"
#include "server_Cliente.h"

ServidorEx::ServidorEx(Servidor* servidor) {
	this->servidor = servidor;
	this->socket = new MSocket(servidor->getPuerto(), servidor->getCantClientes());

	int retorno = this->socket->listen(servidor->getPuerto(), servidor->getCantClientes());
	if (retorno != 0) {
		isValido = false;
	} else {
		isValido = true;
	}
}

MSocket* ServidorEx::getSocket(){
	return socket;
}

bool ServidorEx::getIsValido(){
	return isValido;
}
void* ServidorEx::run(){
	std::cout << "run del server que escucha para aceptar " << std::endl;

		this->servidor->setEstado(true);
		while (this->servidor->getEstado()) {
			MSocket* socketCliente = this->socket->accept();
			std::cout << "Termina el  accept";
			if (socketCliente != NULL) {
				std::cout << "voy a crear un cliente " << std::endl;

				/*hay un cliente*/
				Cliente* cliente = new Cliente(socketCliente, this->servidor);
				cliente->execute();
				//borrar cliente en servidor, cuando sale, no????
			}
		}
		return NULL;
}

ServidorEx::~ServidorEx() {
	delete this->socket;
}
