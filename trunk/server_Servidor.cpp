/*
 * Servidor.cpp
 *
 *  Created on: Apr 25, 2009
 *      Author: mmmary
 */

#include "common_Lock.h"
#include  "common_Cambio.h"
#include  "server_Cliente.h"
#include "server_Servidor.h"
#include <iostream>

#define MAXCANTUS 27

Servidor::Servidor(unsigned short puerto, int cantClientes) {
	this->escucho = true;
	this->puerto = puerto;
	this->cantClientes = cantClientes;
	execute();
}

int Servidor::getPuerto() {
	return this->puerto;
}
int Servidor::getCantClientes() {
	return this->cantClientes;
}
std::queue<NombreCambio> Servidor::getColaDeCambios() {
	return this->colaDeCambios;
}

void Servidor::removerCliente(const std::string& nombre) {
	std::list<Cliente*>::iterator it;
	Cliente* clienteAux;
	for (it = getListaClientes()->begin(); it != getListaClientes()->end(); ++it) {
		clienteAux = *it;
		if (clienteAux->getNombre() == nombre) {
			getListaClientes()->remove(clienteAux);
			return;
		}
	}
}

int Servidor::getVersion() {
	return this->documentoConc.getVersion();
}

void* Servidor::run() {
	/*mientras extoy conectado, veo si hay cambios y los proceso*/
	while (escucho) {
		usleep(500);
		if (!colaDeCambios.empty()) {
			this->leerCambios();
		}
	}
	return NULL;
}

void Servidor::agregarCambio(Cambio* cambio, const std::string& nombre) {
	Lock lock(mutex);
	NombreCambio nc(nombre, cambio);
	colaDeCambios.push(nc);
}

void Servidor::leerCambios() {

	Cambio* cambio;
	std::string nombre;
	{
		Lock lock(mutex);
		NombreCambio nc = this->colaDeCambios.front();
		this->colaDeCambios.pop();
		cambio = nc.cambio;
		nombre = nc.nombre;
	}
	/*proceso el cambio*/
	if (cambio->getVersion() == this->getVersion()) {
		this->procesarCambio(cambio, nombre);
	} else {
		switch (cambio->getTipo()[0]) {
		case 'A': {

			/*aviso que rechazo el cambio, para que lo borre de su vista*/

			Cambio cambio2("B", (cambio->getVersion()) + 1, 2,
					cambio->getPosicion(), cambio->getTexto());
			this->enviarCambio(cambio2, nombre, 1);
			break;
		}
		case 'B': {
			/*aviso que rechazo el cambio de borrado, para que lo agregue a la vista*/

			Cambio cambio2("A", (cambio->getVersion()) + 1, 2,
					cambio->getPosicion(), cambio->getTexto());
			this->enviarCambio(cambio2, nombre, 1);
			break;
		}

		case 'E': {
			/*este cambio se procesa aunque tenga cualquier numero de version*/
			this->procesarCambio(cambio, nombre);
			break;
		}
		}

	}
	delete cambio;
}

void Servidor::desconectarCliente(const std::string& nombre) {
	std::list<Cliente*>::iterator it;
	Cliente* clienteAux;
	for (it = this->getListaClientes()->begin(); it
			!= this->getListaClientes()->end(); ++it) {
		clienteAux = *it;

		if (nombre == clienteAux->getNombre()) {

			clienteAux->desloguearCliente();
			clienteAux->join();
			removerCliente(clienteAux->getNombre());
			delete clienteAux;
			return;
		}
	}
}

void Servidor::procesarCambio(Cambio* cambio, const std::string& nombre) {

	switch (cambio->getTipo()[0]) {
	case 'N': {
		/*se maneja desde el server_cliente */
		break;
	}

	case 'A': {

		this->documentoConc.agregarTexto(cambio->getTexto(),
				cambio->getPosicion());

		/*les envio a todos el cambio, con el numero de version aumentado*/
		Cambio cambio2(cambio->getTipo(), (cambio->getVersion()) + 1, 0,
				cambio->getPosicion(), cambio->getTexto());
		this->enviarCambio(cambio2, nombre, 0);

		break;
	}
	case 'B': {
		this->getDocumentoConc()->borrarTexto(cambio->getTexto(),
				cambio->getPosicion());
		/*les envio a todos el cambio con el numero de version aumentado*/
		Cambio cambio2(cambio->getTipo(), (cambio->getVersion()) + 1, 0,
				cambio->getPosicion(), cambio->getTexto());
		this->enviarCambio(cambio2, nombre, 0);
		break;
	}

	case 'E': {
		Lock lock(this->mutex);

		/*le envio al cliente su cambio para que se desloguee y dentro llamo a desloguearCliente()*/
		this->enviarCambio(*cambio, cambio->getTexto(), 1);

		Cambio cambio2("O", cambio->getTexto());
		this->enviarCambio(cambio2, cambio->getTexto(), 0);
		desconectarCliente(cambio->getTexto());

		break;
	}
	}
}

bool Servidor::getEstado() {
	return escucho;
}
void Servidor::setEstado(bool estado) {
	this->escucho = estado;
}

void Servidor::cerrarServidor() {

	char ingreso;
	do {
		std::cout << "Escriba c para cerrar la aplicacion " << std::endl;

		std::cin >> ingreso;
	} while (ingreso != 'c');
	std::cout << "La aplicacion se esta cerrando..." << std::endl;

	/*borro a todos los clientes*/

	std::list<Cliente*>::iterator it;
	Cliente* clienteAux;
	for (it = this->getListaClientes()->begin(); it
			!= this->getListaClientes()->end(); ++it) {
		clienteAux = *it;
		this->desconectarCliente(clienteAux->getNombre());

	}
	while (!colaDeCambios.empty()) {
		NombreCambio nc = this->colaDeCambios.front();
		this->colaDeCambios.pop();
		delete nc.cambio;
	}

	this->setEstado(false);
	this->join();
}

std::list<Cliente*>* Servidor::getListaClientes() {
return &listaDeClientes;
}

DocumentoConcurrente* Servidor::getDocumentoConc() {
	return &this->documentoConc;
}

void Servidor::notificarAmigoConectado(const std::string& nombre) {
	/*a todos les aviso que su amigo se conecto*/
	Lock lock(this->mutex);
	Cambio cambio("F", nombre);
	this->enviarCambio(cambio, nombre, 0);
}

void Servidor::crearListaAmigos(Cliente* cliente) {
	/*al nuevo cliente le mando una lista de todos sus amigos conectados*/
	Lock lock(this->mutex);
	std::list<Cliente*>::iterator it;
	Cliente* clienteAux;
	for (it = this->getListaClientes()->begin(); it
			!= this->getListaClientes()->end(); ++it) {
		clienteAux = *it;
		Cambio cambio("F", clienteAux->getNombre());
		this->enviarCambio(cambio, cliente->getNombre(), 1);
	}
}

void Servidor::verificacionCliente(Cliente* cliente) {
	bool encontrado = false;

	{
		Lock lock(this->mutex);
		std::list<Cliente*>::iterator it;
		Cliente* clienteAux;
		for (it = this->getListaClientes()->begin(); ((it
				!= this->getListaClientes()->end()) && (!encontrado)); ++it) {
			clienteAux = *it;
			if (clienteAux->getNombre() == cliente->getNombre()) {
				encontrado = true;
				/*el cliente ya esta en la lista*/
			}
		}
	}

	std::string tipo;
	if (encontrado) {
		tipo = "R";
		/*ya existe el cliente con ese nombre*/
		Cambio cambio(tipo, cliente->getNombre());
			Parser parser;
			std::string str = parser.toString(cambio);
		cliente->getSocket()->send(str);
		cliente->desloguearCliente();
	} else {
		tipo = "L";

		this->notificarAmigoConectado(cliente->getNombre());
		this->getListaClientes()->push_back(cliente);
		this->crearListaAmigos(cliente);

		Cambio cambio(tipo, cliente->getNombre());
		this->enviarCambio(cambio, cliente->getNombre(), 1);

		/*le envio el documento*/
		std::string contenido =
				this->documentoConc.getDocumento()->getContenido();
		Cambio
				documento("D", this->getDocumentoConc()->getVersion(),
						contenido);
		this->enviarCambio(documento, cliente->getNombre(), 1);
	}

}
void Servidor::enviarCambio(Cambio cambio, const std::string& nombre, int flag) {
	if (flag == 0) {
		/*le mando a todos el cambio creado*/
		std::list<Cliente*>::reverse_iterator it;
		Cliente* clienteAux;
		for (it = this->getListaClientes()->rbegin(); it
				!= this->getListaClientes()->rend(); ++it) {
			clienteAux = *it;
			if (nombre != clienteAux->getNombre()) {
				clienteAux->getSocket()->send(cambio.getStdCambio());
			} else {
				if (cambio.getTipo() != "O") {
					/*le envio al cliente el cambio pero con un alcance = 1*/
					Cambio cambio2(cambio.getTipo(), cambio.getVersion(), 1,
							cambio.getPosicion(), cambio.getTexto());
					clienteAux->getSocket()->send(cambio2.getStdCambio());
				}
			}
		}
	} else {
		/*solo se lo envio al que creo el mensaje*/
		std::list<Cliente*>::reverse_iterator it;
		Cliente* clienteAux;
		for (it = this->getListaClientes()->rbegin(); it
				!= this->getListaClientes()->rend(); ++it) {
			clienteAux = *it;
			if (nombre == clienteAux->getNombre()) {
				clienteAux->getSocket()->send(cambio.getStdCambio());
			}
		}
	}
}

Servidor::~Servidor() {
}
