/*
 * Cliente.cpp
 *
 *  Created on: May 3, 2009
 *      Author: mmmary
 */
//#include <glib.h>
//#include <glib/gprintf.h>

#include <gtk/gtk.h>
#include "client_Cliente.h"
#include "common_Lock.h"
#include "client_Vista.h"
#include <iostream>
#include <string.h>

#define TAMANIIO  1024
#define MAXINTENTOS 20
#define MAXCANTUS 27

Cliente::Cliente() {
	std::cout << "////CREO CLIENTE/////" << std::endl;
	this->setConectado(false);
	this->documentoConc = new DocumentoConcurrente();
}

void Cliente::setNombre(const std::string& nombre) {
	this->nombre = nombre;
}

std::string Cliente::getNombre() {
	return this->nombre;
}
void Cliente::inicializar(const char* ip, const char* port, GtkWidget* boton) {

	this->conectarSocket(ip, port);

	if (!this->getConectado()) {
		this->vista->ErrorConectar();
		gtk_widget_set_sensitive(boton, true);

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
		std::cout << "me pude conectar " << std::endl;
		this->puerto = puerto;
		this->setConectado(true);

	}
}

void Cliente::enviarDatosInicio() {

	Cambio cambio("N", this->nombre);
	int cant = 0;
	int retorno = -1;
	while ((retorno == -1) && (cant < MAXINTENTOS)) {
		cant++;
		retorno = this->socket->send(cambio.getStdCambio());
	}
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
	std::cout << nombre << " se ha deslogueado" << std::endl;

	/*debo desbloquear el recv, para q se pueda hacer el join*/
	Cambio cambio("E", nombre);
	/*se lo envio al servidor*/
	this->enviarCambio(cambio);
	std::cout << " el cambio enviado: " << cambio.getStdCambio() << std::endl;
}

void Cliente::ejecutarAccion(Parser parser) {
	std::cout << "Empiezo a ejecutar una accion " << std::endl;
	switch (parser.getTipo()[0]) {

	case 'E': {
		std::cout << "recibi la E" << std::endl;
		this->socket->close();
		this->setConectado(false);

		break;
	}

	case 'D': {
/*se setea el documento*/
		this->documentoConc->setDocumento(parser.getTexto());
		std::cout << "el documento luego"
				<< this->documentoConc->getDocumento()->getContenido()
				<< std::endl;
		/*se setea la version */
		this->documentoConc->setVersion(parser.getVersion());
		/*se modifica la vista*/
		this->vista->cargarDocumento(parser.getTexto());


		break;
	}
	case 'L': {
		/*me aceptaron*/
		break;
	}
	case 'R': {

		/*lanzo ventana de error, pues  el nombre de usuario esta ya ocupado*/
		GtkWidget
				* ventanaerror =
						gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL,
								GTK_MESSAGE_WARNING, GTK_BUTTONS_OK,
								"El nombre de Usuario ya ha sido elegido.\n Ingrese otro diferente");
		gtk_window_set_title(GTK_WINDOW(ventanaerror), "Error");
		gtk_dialog_run( GTK_DIALOG(ventanaerror));
		gtk_widget_destroy(ventanaerror);
		gtk_widget_set_sensitive(this->vista->getVentana()->getBotonDeslog(),
				true);


	}

	case 'A': {

		if ((parser.getAlcance() == 0) || (parser.getAlcance() == 1)) {

			/* el documento  se modifica*/
			this->documentoConc->agregarTexto(parser.getTexto(),
					parser.getPosicion());
			std::cout << "el doc es "
					<< documentoConc->getDocumento()->getContenido()
					<< std::endl;
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

			this->documentoConc->borrarTexto(parser.getTexto(),
					parser.getPosicion());
		}
		if ((parser.getAlcance() == 0) || (parser.getAlcance() == 2)) {
			/*la vista se modifica*/

			this->vista->borrar(parser.getTexto().c_str(), parser.getPosicion());
		}
		break;

	}
	case 'F': {

		std::string str = parser.getTexto();
		if (this->listaDeAmigos.empty()) {
			/*no tengo amigos =( , ahora tengo uno*/

			std::cout << "me llego el primer amigo " << std::endl;
			str += "\n";
			gtk_text_buffer_set_text(this->vista->getVentana()->getLista(),
					str.c_str(), -1);

		} else {
			this->vista->agregarAmigo(str.c_str());

		}
		this->agregarAmigo(parser.getTexto());
		break;
	}

	case 'O': {
		/*debo quitar a un amigo de mi lista y de la vista*/

			this->quitarAmigo(parser.getTexto());

		break;
	}
	}

}

void* Cliente::run() {
//TODO BORRAR Comentarios
	std::cout << "Cliente::run()" << std::endl;

	char buff1[TAMANIIO];
	bzero(buff1, TAMANIIO);
	std::string str;
	while (getConectado()) {
		std::cout << "ESTOY CONECTADO " << std::endl;

		int cantidad = 0;
		Parser parser;

		cantidad = this->socket->recieve(buff1, TAMANIIO - 1);
		std::cout << "recibi! "<<buff1 << std::endl;

		if (cantidad <= 0) {
			std::cout << "cantidad es "<<cantidad<<"por lo q cierro este cliente" << std::endl;

			this->setConectado(false);
			//?break;
		}

		if (this->getConectado()) {
			buff1[cantidad] = '\0';
			str += buff1;
		}

		while ((this->getConectado()) && (parser.procesar(str.c_str(),
				&cantidad))) {
			std::cout << "termino de procesar " << cantidad
					<< " bytes del buffer" << std::endl;

			if (cantidad > 0) {
				/*borro lo q ya lei del buffer*/
				str.erase(0, cantidad);
				cantidad = str.size();
			}
			std::cout << "quedan en el buffer: " << cantidad << std::endl;
			std::cout << "el cambio recibido es "
					<< parser.toCambio()->getStdCambio() << std::endl;

			this->ejecutarAccion(parser);
			std::cout << "luego de accion " << std::endl;

			parser.reset();
			std::cout << "luego de accion 2" << std::endl;

		}
		if (this->getConectado()) {
			str.erase(0, cantidad);
			cantidad = str.size();
			std::cout << "lluego de accion 3 " << std::endl;

		}
		std::cout << "lluego de accion 4 " << std::endl;

		/*saco ese mensaje del buffer*/
	}
	std::cout << "sali del run de cliente!!!!!!!" << std::endl;
	return NULL;
}

void Cliente::enviarCambio(Cambio cambio) {
	int retorno = -1;
	int cant = 0;
	while ((retorno == -1) && (cant < MAXINTENTOS)) {
		retorno = this->socket->send(cambio.getStdCambio());
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

}

DocumentoConcurrente* Cliente::getDocumentoConc() {
	return this->documentoConc;
}
Cliente::~Cliente() {
	delete this->documentoConc;
	std::cout << "////BORRO CLIENTE/////" << std::endl;
	// TODO Auto-generated destructor stub
	//se llama a destr de socket
}
