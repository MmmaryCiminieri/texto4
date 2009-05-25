/*
 * Servidor.cpp
 *
 *  Created on: Apr 25, 2009
 *      Author: mmmary
 */

#include <glib.h>
#include <glib/gprintf.h>
#include <gtk/gtk.h>

#include "common_Lock.h"
#include  "common_Cambio.h"
#include  "server_Cliente.h"
//borrar include iter
#include "server_Servidor.h"
#include "common_Iterador.h"


#define MAXCANTUS 27

Servidor::Servidor(unsigned short puerto, int cantClientes) {
	this->escucho = true;
	this->puerto = puerto;
	this->cantClientes = cantClientes;
	this->colaDeCambios = new Cola<NombreCambio> ;
	execute();
}

int Servidor::getPuerto() {
	return this->puerto;
}
int Servidor::getCantClientes() {
	return this->cantClientes;
}
Cola<NombreCambio>* Servidor::getColaDeCambios() {
	return this->colaDeCambios;
}


unsigned short setPuerto(){
	//TODO
}

int Servidor::getVersion() {
	return this->documentoConc.getVersion();
}
void* Servidor::run() {
	/*mientras extoy conectado, veo si hay cambios y los proceso*/
	std::cout << "ESTOY EN EL RUN" << std::endl;

	while (escucho) {
		usleep(500);

		if (!colaDeCambios->isEmpty()) {
			std::cout << "ACABO DE LEER UN CAMBIO" << std::endl;
			this->leerCambios();
		}

	}
	std::cout << "deje de estar conectado" << std::endl;

	return NULL;
}

void Servidor::agregarCambio(Cambio* cambio, std::string nombre) {
	Lock lock(mutex);
	NombreCambio nc(nombre, cambio);
	colaDeCambios->push(nc);
}

void Servidor::leerCambios() {

	Cambio* cambio;
	std::string nombre;
	{
		Lock lock(mutex);
		NombreCambio nc = this->colaDeCambios->pop();
		cambio = nc.cambio;
		nombre = nc.nombre;
	}
	/*proceso el cambio*/
	std::cout << "procesare el cambio: " << cambio->getStdCambio() << std::endl;
	if (cambio->getVersion() == this->getVersion()) {
		this->procesarCambio(cambio, nombre);
	} else {
		/*aviso que rechazo el cambio, para que lo borre de su vista*/
		if (cambio->getTipo() == "A") {
			Cambio cambio2("B", (cambio->getVersion()) + 1,2,
					cambio->getPosicion(), cambio->getTexto());
			this->enviarCambio(cambio2, nombre, 1);
		}

		/*aviso que rechazo el cambio de borrado, para que lo agregue a la vista*/

		if (cambio->getTipo() == "B") {

			Cambio cambio2("A", (cambio->getVersion()) + 1,2,
					cambio->getPosicion(), cambio->getTexto());
			this->enviarCambio(cambio2, nombre, 1);

		}

	}
delete cambio;
}


void Servidor::procesarCambio(Cambio* cambio, std::string nombre) {

	switch (cambio->getTipo()[0]) {
	case 'N': {
		/*se maneja desde el server_cliente */
		break;
	}


	case 'A': {
		std::cout << "agregar del server" << std::endl;

		this->documentoConc.agregarTexto(cambio->getTexto(),
				cambio->getPosicion());
		std::cout << "el doc " << documentoConc.getDocumento()->getContenido()
				<< std::endl;

		/*les envio a todos el cambio, con el numero de version aumentado*/
		Cambio cambio2(cambio->getTipo(), (cambio->getVersion()) + 1,0,
				cambio->getPosicion(), cambio->getTexto());
		this->enviarCambio(cambio2, nombre, 0);

		break;
	}
	case 'B': {
		this->getDocumentoConc()->borrarTexto(cambio->getTexto(),
				cambio->getPosicion());
		/*les envio a todos el cambio con el numero de version aumentado*/
		Cambio cambio2(cambio->getTipo(), (cambio->getVersion()) + 1,0,
				cambio->getPosicion(), cambio->getTexto());
		this->enviarCambio(cambio2, nombre, 0);
		break;
	}

	case 'O': {
		Lock lock(this->mutex);
		this->listaDeClientes.remover(cambio->getTexto());
		Cambio cambio2(cambio->getTipo(),  cambio->getTexto());
		this->enviarCambio(cambio2, cambio->getTexto(), 0);

		//todo cerrar ese socket
		//cerrar ese run
		break;
	}
	case 'D':
			;
		case 'L':
			;
		case 'R':
			;
		case 'F': {
			/*no se pueden  dar de este lado*/
			break;
		}
	}
}

MSocket* Servidor::getSocket() {
	return this->socket;
}

bool Servidor::getEstado() {
	return escucho;
}
void Servidor::setEstado(bool estado) {
	this->escucho = estado;
}

void Servidor::cerrarServidor() {

	//ver q ingrese usuario
	std::cout << "escriba c para cerrar la aplicacion " << std::endl;
	char ingreso;
	std::cin >> ingreso;
	if (ingreso == 'c') {
		std::cout << "la aplicacion se esta cerrando..." << std::endl;

		//this->socket->close();
		this->setEstado(false);

		/*borro a todos los clientes*/

		Iterador<Cliente*> it =
				this->getListaClientes()->getLista()->iterador();

		while (it.hasNext()) {

			Cliente* clienteAux = it.next();
			clienteAux->join();

			std::cout << "join de un cliente... " << std::endl;

		}
		std::cout << "antes del join del server..." << std::endl;
		this->join();
		std::cout << "luego del join del server... " << std::endl;

	}
}

ListaClientes* Servidor::getListaClientes() {
	return &this->listaDeClientes;
}

DocumentoConcurrente* Servidor::getDocumentoConc() {
	return &this->documentoConc;
}

void Servidor::notificarAmigoConectado(std::string nombre) {
	/*a todos les aviso que su amigo se conecto*/
	Lock lock(this->mutex);
	Cliente* clienteAux;
	Cambio cambio("F", nombre);

	Iterador<Cliente*> it = this->getListaClientes()->getLista()->iterador();
	while (it.hasNext()) {
		clienteAux = it.next();

		clienteAux->getSocket()->send(cambio.getStdCambio());
	}
}

void Servidor::crearListaAmigos(Cliente* cliente) {
	/*al nuevo cliente le mando una lista de todos sus amigos conectados*/
	Lock lock(this->mutex);
	Cliente* clienteAux;

	Iterador<Cliente*> it = this->getListaClientes()->getLista()->iterador();
	while (it.hasNext()) {
		clienteAux = it.next();
		Cambio cambio("F", clienteAux->getNombre());

		cliente->getSocket()->send(cambio.getStdCambio());
	}
}

void Servidor::VerificacionCliente(Cliente* cliente) {
	bool encontrado = false;

	{
		Lock lock(this->mutex);
		Cliente* clienteAux;

		Iterador<Cliente*> it =
				this->getListaClientes()->getLista()->iterador();
		while (it.hasNext() && (!encontrado)) {
			clienteAux = it.next();
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
		//TODO borrarlo a este
	} else {
		tipo = "L";
		this->notificarAmigoConectado(cliente->getNombre());
		this->crearListaAmigos(cliente);
		this->getListaClientes()->getLista()->add(cliente);

	}

	Cambio cambio(tipo, cliente->getNombre());
	int cant = 0;
	int retorno = -1;
	while ((retorno == -1) && (cant < 20)) {
		std::cout << "El cambio a mandar esS: \n" << cambio.getStdCambio()
				<< std::endl;
		cant++;
		//std::cout<<"el cambio es:"<<cambio.getStdCambio()<< std::endl;
		retorno = cliente->getSocket()->send(cambio.getStdCambio());

	}
	if(tipo =="L"){
	/*le envio el documento*/
	std::string contenido = this->documentoConc.getDocumento()->getContenido();
	Cambio documento("D", this->getDocumentoConc()->getVersion(), contenido);
	cant = 0;
	retorno = -1;
	while ((retorno == -1) && (cant < 20)) {
		std::cout << "El documento a mandar es: \n" << documento.getStdCambio()
				<< std::endl;
		cant++;
		retorno = cliente->getSocket()->send(documento.getStdCambio());

	}

	}

}
void Servidor::enviarCambio(Cambio cambio, std::string nombre, int flag) {
	if (flag == 0) {
		/*le mando a todos el cambio creado*/
		Cliente* clienteAux;
		Iterador<Cliente*> it =
				this->getListaClientes()->getLista()->iterador();
		while (it.hasNext()) {
			clienteAux = it.next();
			if (nombre != clienteAux->getNombre()) {

				clienteAux->getSocket()->send(cambio.getStdCambio());

			} else {

				/*le envio al cliente el cambio pero con un alcance = 1*/
					Cambio cambio2(cambio.getTipo(), cambio.getVersion(),1,
							cambio.getPosicion(), cambio.getTexto());
					std::cout << "lo q envio " << cambio2.getStdCambio()
							<< std::endl;

					clienteAux->getSocket()->send(cambio2.getStdCambio());

			}
		}
	} else {
		/*solo se lo envio al que creo el mensaje*/
		Cliente* clienteAux;
		Iterador<Cliente*> it =
				this->getListaClientes()->getLista()->iterador();
		while (it.hasNext()) {
			clienteAux = it.next();
			if (nombre == clienteAux->getNombre()) {
				clienteAux->getSocket()->send(cambio.getStdCambio());
			}
		}

	}
}

Servidor::~Servidor() {
	std::cout << "destructor del server " << std::endl;

	delete this->colaDeCambios;
}
