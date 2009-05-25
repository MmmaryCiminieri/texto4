/*
 * Cliente.cpp
 *
 *  Created on: Apr 25, 2009
 *      Author: mmmary
 */

#include <string.h>
#include "server_Cliente.h"
#include "common_Parser.h"
#include  "common_Iterador.h"
#define TAMANIIO 1024
Cliente::Cliente(MSocket * socket, Servidor* servidor) {
	this->socket = socket;
	this->servidor = servidor;
	this->conectado = true;

}

void Cliente::setNombre(std::string nombre) {
	this->nombre = nombre;
}

std::string Cliente::getNombre() {
	return this->nombre;
}

MSocket* Cliente::getSocket() {
	return this->socket;
}

void Cliente::ejecutarAccion(Parser parser) {
char ch = (parser.getTipo())[0];

switch (ch){

	case 'N': {
		this->setNombre(parser.getTexto());
		this->servidor->VerificacionCliente(this);
		break;
	}
	case 'D': ; case 'L':; case 'R':; case 'F':{
		//no se puede dar
		break;
	}

	case 'A':; case 'B':;	case 'O': {
		std::cout << "algun cliente le avisa a todos q quiere agregar/borrar data o salir" << std::endl;

		/*recibo un cambio, y si tenemos la misma version lo recibo*/
			this->servidor->agregarCambio(parser.toCambio(), nombre);

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


	if (cantidad <= 0) {
				this->conectado = false;
				//?break;
			}

			if (conectado) {
				buff1[cantidad] = '\0';
				str += buff1;
			}



	while ((conectado) && (parser.Procesar(str.c_str(), &cantidad))) {

		std::cout << "termino de procesar " << cantidad
		<< "bytes sdel buffer" << std::endl;

		/*borro lo q ya lei del buffer*/

		if (cantidad > 0) {
			/*borro lo q ya lei del buffer*/
			str.erase(0, cantidad);
			cantidad = str.size();
		}
		std::cout << "quedan en el buffer: " << cantidad << std::endl;

		this->ejecutarAccion(parser);
		parser.reset();

	}
	if (conectado) {
		str.erase(0, cantidad);
		cantidad = str.size();
	}

	/*saco ese mensaje del buffer*/
}

std::cout << "deje de escuchar" << std::endl;

return NULL;
}

Cliente::~Cliente() {
	/* borra su socket */
	std::cout << "destructor del cliente " << std::endl;
	delete this->socket;
}
