/*
 * Cliente.cpp
 *
 *  Created on: May 3, 2009
 *      Author: mmmary
 */
#include <gtk/gtk.h>
#include "client_Cliente.h"
#include "common_Lock.h"
#include "client_Vista.h"
#include <iostream>
#include <netdb.h>
#include <string.h>

#define TAMANIIO  1024
#define MAXINTENTOS 20
#define MAXCANTUS 27

Cliente::Cliente() {
	this->setConectado(false);
}

void Cliente::setNombre(const std::string& nombre) {
	this->nombre = nombre;
}

std::string Cliente::getNombre() {
	return this->nombre;
}

bool Cliente::isAceptado() {
	Lock lock(this->mutex);
	return aceptado;
}

void Cliente::setAceptado(bool status) {
	Lock lock(mutex);
	aceptado = status;

}
void Cliente::inicializar(const char* ip, const char* port, GtkWidget* boton) {

	this->conectarSocket(ip, port);

	if (!this->getConectado()) {
		this->vista->errorConectar();
		gtk_widget_set_sensitive(boton, true);
		gtk_text_view_set_editable(GTK_TEXT_VIEW(this->vista->getVentana()->getView()), false);
this->vista->getVentana()->desloguearCliente();

	} else {
		/*valido existencia*/
		this->enviarDatosInicio();
		/*escucho cambios del servidor*/
		this->execute();


	}
}
MSocket* Cliente::getSocket() {
	return this->socket;
}

void Cliente::setVista(Vista* vista) {
	this->vista = vista;
}

void Cliente::conectarSocket(const char* IP, const char* puerto) {

	this->socket = new MSocket();

	int retorno = this->socket->connect(IP, puerto);
	if (retorno == 0) {
		this->puerto = puerto;
		this->setConectado(true);

	}
}

void Cliente::enviarDatosInicio() {

	Cambio cambio("N", this->nombre);
	Parser parser;
	std::string str = parser.toString(cambio);
	this->enviarCambio(cambio);
}

bool Cliente::getConectado() {
	Lock lock(this->mutex);
	return conectado;
}

void Cliente::setConectado(bool newStatus) {
	Lock lock(this->mutex);
	conectado = newStatus;
}

void Cliente::desloguearse() {
	/*el cliente se deloguea*/
	/*debo desbloquear el recv, para q se pueda hacer el join*/
	Cambio cambio("E", nombre);
	/*se lo envio al servidor*/
	this->enviarCambio(cambio);
}

char Cliente::ejecutarAccion(Parser parser) {
	char tipoAProcesar = parser.getTipo()[0];
	switch (tipoAProcesar) {

	case 'E': {
		this->socket->shutdown();
		this->setConectado(false);
		break;
	}
	case 'D': {
		/*se setea el documento*/
		this->documentoConc.setDocumento(parser.getTexto());
		/*se setea la version */
		this->documentoConc.setVersion(parser.getVersion());
		/*se modifica la vista*/
		this->vista->cargarDocumento(parser.getTexto());
		break;
	}
	case 'R': {

		gtk_widget_set_sensitive(this->vista->getVentana()->getBotonDeslog(),
				false);
		gtk_widget_set_sensitive(this->vista->getVentana()->getBoton(),
						true);
		gtk_text_view_set_editable(GTK_TEXT_VIEW(this->vista->getVentana()->getView()), false);

		this->vista->getVentana()->desloguearCliente();
		//this->vista->errorConectar();

break;
	}
	case 'L': {
		/* Fui aceptado */
		setAceptado(true);
		break;

	}
	case 'A': {
		if ((parser.getAlcance() == 0) || (parser.getAlcance() == 1)) {
			/* el documento  se modifica*/
			this->documentoConc.agregarTexto(parser.getTexto(),
					parser.getPosicion());
		}
		if ((parser.getAlcance() == 0) || (parser.getAlcance() == 2)) {
			/*la vista se modifica*/
			this->vista->agregar(parser.getTexto().c_str(),
					parser.getPosicion());
		}
		break;
	}
	case 'B': {
		if ((parser.getAlcance() == 0) || (parser.getAlcance() == 1)) {
			/* el documento  se modifica*/
			this->documentoConc.borrarTexto(parser.getTexto(),
					parser.getPosicion());
		}
		if ((parser.getAlcance() == 0) || (parser.getAlcance() == 2)) {
			/*la vista se modifica*/
			this->vista->borrar(parser.getTexto().c_str(), parser.getPosicion());
		}
		break;

	}
	case 'F': {
		this->agregarAmigo(parser.getTexto());
		break;
	}

	case 'O': {
		/*debo quitar a un amigo de mi lista y de la vista*/
		this->quitarAmigo(parser.getTexto());
		break;
	}
	}
	return tipoAProcesar;

}

void* Cliente::run() {
	std::string str;
	char tipo = 'E';
	while (getConectado()) {

		char buff1[TAMANIIO];
		bzero(buff1, TAMANIIO);
		int cantidad = 0;
		Parser parser;

		cantidad = this->socket->recieve(buff1, TAMANIIO - 1);

		if (cantidad <= 0) {
			this->setConectado(false);
		}


		if (this->getConectado()) {
			buff1[cantidad] = '\0';
			str += buff1;
		}

		while ((this->getConectado()) && (parser.procesar(str.c_str(),
				&cantidad))) {

			if (cantidad > 0) {
				/*borro lo q ya lei del buffer*/
				str.erase(0, cantidad);
				cantidad = str.size();
			}

			tipo =this->ejecutarAccion(parser);
			parser.reset();
		}


		if (this->getConectado()) {
			str.erase(0, cantidad);
			cantidad = str.size();
		} else if (tipo != 'E') {
			this->vista->getVentana()->refrescar();
		}

		/*saco ese mensaje del buffer*/
	}
	return NULL;
}

void Cliente::enviarCambio(const Cambio& cambio) {
	int retorno = -1;
	int cant = 0;
	Parser parser;
	std::string str = parser.toString(cambio);
	while ((retorno == -1) && (cant < MAXINTENTOS)) {
		retorno = this->socket->send(str);
		cant++;
	}
}

std::list<std::string> Cliente::getAmigos() {
	return this->listaDeAmigos;
}
void Cliente::quitarAmigo(const std::string& nombre) {
	this->listaDeAmigos.remove(nombre);
	this->vista->refrescarLista();
}

void Cliente::agregarAmigo(const std::string& nombre) {
	this->listaDeAmigos.push_back(nombre);
	this->vista->agregarAmigo(nombre);
}

DocumentoConcurrente* Cliente::getDocumentoConc() {
	return &documentoConc;
}

Cliente::~Cliente() {
	delete this->socket;
}
