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

void ServidorEx::dejarDeEscuchar(){
	socket->close();
	std::cout << "ServidorEx::dejarDeEscuchar() - socket cerrado" << std::endl;
	//join(); TODO: No se que pasa :( de este join no vuelve nunca, porque el accept del socket esta bloqueado por mas que lo cierre
}

ServidorEx::~ServidorEx() {
	std::cout << "ServidorEx::~ServidorEx()" << std::endl;
	delete this->socket;
}
