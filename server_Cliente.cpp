/*
 * Cliente.cpp
 *
 *  Created on: Apr 25, 2009
 *      Author: mmmary
 */
#include <iostream>
#include <string.h>

#include "server_Cliente.h"
#include "server_Servidor.h"
#include "common_Parser.h"
#include "common_Lock.h"
#define TAMANIIO 1024

Cliente::Cliente(MSocket * socket, Servidor* servidor) {
	this->socket = socket;
	this->servidor = servidor;
	/*es true por que el socket ya se conecto*/
	this->conectado = true;
}

void Cliente::setNombre(const std::string& nombre) {
	this->nombre = nombre;
}

std::string Cliente::getNombre() const {
	return this->nombre;
}

MSocket* Cliente::getSocket() {
	return this->socket;
}

bool  Cliente::getConectado() {
	Lock lock(mutex);
	return conectado;
}

void  Cliente::setConectado(bool status){
	Lock lock(mutex);
	this->conectado = status;
}

void Cliente::desloguearCliente(){
	this->socket->close();
	this->setConectado(false);
}

void Cliente::ejecutarAccion(Cambio* cambio) {
	switch (cambio->getTipo()[0]) {

	case 'N': {
		/*el cliente envia sus datos para ingresar al sistema*/
		this->setNombre(cambio->getTexto());
		this->servidor->verificacionCliente(this);
		break;
	}
	case 'A':; case 'B':; case 'O':; case 'E': {
		/*recibo un cambio que afectarÃ¡ al documeto o a los usuarios conectados */
		/*estos cambios de acolan, esperando a ser procesados*/
		this->servidor->agregarCambio(cambio, nombre);
		break;
	}

	}
}

void* Cliente::run() {
	std::cout << "dentro del run " << std::endl;
	char buff1[TAMANIIO];
	bzero(buff1, TAMANIIO);
	std::string str;

	while (this->conectado) {

		int cantidad = 0;
		Parser parser;

		cantidad = this->socket->recieve(buff1, TAMANIIO - 1);

		std::cout << "en el reun del cliente me llega: " << buff1 << std::endl;
		if (cantidad <= 0) {
			this->conectado = false;
		} else {
			buff1[cantidad] = '\0';
			str += buff1;
		}

		while ((conectado) && (parser.procesar(str.c_str(), &cantidad))) {

			std::cout << "termino de procesar " << cantidad
					<< "bytes sdel buffer" << std::endl;

			if (cantidad > 0) {
				/*borro lo q ya lei del buffer*/
				str.erase(0, cantidad);
				cantidad = str.size();
			}

			std::cout << "quedan en el buffer: " << cantidad << std::endl;

			//delete
			Cambio* cambio = new Cambio;
			cambio = parser.toCambio();
			this->ejecutarAccion(cambio);
			parser.reset();

		}
		if (conectado) {
			/*saco ese mensaje del buffer(pueden venirme mas de uno)*/
			str.erase(0, cantidad);
			cantidad = str.size();
		}

	}

	std::cout << " salgo del run del cliente(server)" << std::endl;
	return NULL;
}

Cliente::~Cliente() {
	/* borra su socket */
	std::cout << "destructor del cliente " << std::endl;
	delete this->socket;
}
