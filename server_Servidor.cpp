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
	//this->listaDeClientes = new ListaClientes();

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

void Servidor::removerCliente(const std::string& nombre){
	 std::list<Cliente*>::iterator it;
Cliente* clienteAux;
	 for( it = getListaClientes()->begin(); it != getListaClientes()->end(); ++it ) {
	       clienteAux = *it;
	       if(clienteAux->getNombre() == nombre){
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
	std::cout << "ESTOY EN EL RUN" << std::endl;

	while (escucho) {
		usleep(500);

		if (!colaDeCambios.empty()) {
			std::cout << "ACABO DE LEER UN CAMBIO" << std::endl;
			this->leerCambios();
		}

	}
	std::cout << "deje de estar conectado" << std::endl;

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
		 for( it = this->getListaClientes()->begin(); it != this->getListaClientes()->end(); ++it ) {
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
		std::cout << "agregar del server" << std::endl;

		this->documentoConc.agregarTexto(cambio->getTexto(),
				cambio->getPosicion());
		std::cout << "el doc " << documentoConc.getDocumento()->getContenido()
				<< std::endl;

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
		std::cout << "E del server" << std::endl;

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

		 std::list<Cliente*>::iterator it;
		Cliente* clienteAux;
			 for( it = this->getListaClientes()->begin(); it != this->getListaClientes()->end(); ++it ) {
			       clienteAux = *it;

			clienteAux->join();

			std::cout << "join de un cliente... " << std::endl;

		}
		std::cout << "antes del join del server..." << std::endl;
		this->join();
		std::cout << "luego del join del server... " << std::endl;

	}
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
	Parser parser;
		std::string str = parser.toString(cambio);

	std::list<Cliente*>::iterator it;
	Cliente* clienteAux;
		 for( it = this->getListaClientes()->begin(); it != this->getListaClientes()->end(); ++it ) {
		       clienteAux = *it;
		clienteAux->getSocket()->send(str);
	}
}

void Servidor::crearListaAmigos(Cliente* cliente) {
	/*al nuevo cliente le mando una lista de todos sus amigos conectados*/
	Lock lock(this->mutex);
	Parser parser;

	 std::list<Cliente*>::iterator it;
	Cliente* clienteAux;
		 for( it = this->getListaClientes()->begin(); it != this->getListaClientes()->end(); ++it ) {
		       clienteAux = *it;


		Cambio cambio("F", clienteAux->getNombre());
		std::string str = parser.toString(cambio);

		cliente->getSocket()->send(str);
	}
}

bool Servidor::verificacionCliente(Cliente* cliente) {
	bool encontrado = false;
		Lock lock(this->mutex);
		 std::list<Cliente*>::iterator it;
		Cliente* clienteAux;
			 for( it = this->getListaClientes()->begin(); ((it != this->getListaClientes()->end())&&(!encontrado)); ++it ) {
			       clienteAux = *it;



			if (clienteAux->getNombre() == cliente->getNombre()) {
				encontrado = true;
				/*el cliente ya esta en la lista*/

			}
		}
return encontrado;
}


			void Servidor::rechazoCliente(Cliente* cliente){

				Cambio cambio("R", cliente->getNombre());
					int cant = 0;
					int retorno = -1;

				this->enviarCambio(cambio, cliente->getNombre(),1);

			}




			void Servidor::ingresoCliente(Cliente* cliente){

		this->notificarAmigoConectado(cliente->getNombre());
		this->crearListaAmigos(cliente);
		this->getListaClientes()->push_back(cliente);

	Cambio cambio("L", cliente->getNombre());
	int cant = 0;
	int retorno = -1;
this->enviarCambio(cambio, cliente->getNombre(), 1);

		/*le envio el documento*/
		std::string contenido =
				this->documentoConc.getDocumento()->getContenido();
		Cambio
				documento("D", this->getDocumentoConc()->getVersion(),
						contenido);

		this->enviarCambio(documento, cliente->getNombre(), 1);



}
void Servidor::enviarCambio(Cambio cambio, const std::string& nombre, int flag) {
	Parser parser;
		std::string str = parser.toString(cambio);

	if (flag == 0) {
		/*le mando a todos el cambio creado*/
		 std::list<Cliente*>::iterator it;
		Cliente*
		clienteAux;
			 for( it = this->getListaClientes()->begin(); it != this->getListaClientes()->end(); ++it ) {

				 clienteAux = *it;

			if (nombre != clienteAux->getNombre()) {

				clienteAux->getSocket()->send(str);

			} else {
				if(cambio.getTipo() != "O"){
				/*le envio al cliente el cambio pero con un alcance = 1*/
				Cambio cambio2(cambio.getTipo(), cambio.getVersion(), 1,
						cambio.getPosicion(), cambio.getTexto());

				clienteAux->getSocket()->send(str);
				}
			}
		}
	} else {
		/*solo se lo envio al que creo el mensaje*/
		 std::list<Cliente*>::iterator it;
		Cliente* clienteAux;
			 for( it = this->getListaClientes()->begin(); it != this->getListaClientes()->end(); ++it ) {
			       clienteAux = *it;

			if (nombre == clienteAux->getNombre()) {
				clienteAux->getSocket()->send(str);


			}
		}
	}
}

Servidor::~Servidor() {
std::cout << "destructor del server " << std::endl;

}
