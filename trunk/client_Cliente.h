/*
 * Cliente.h
 *
 *  Created on: May 3, 2009
 *      Author: mmmary
 */

#ifndef CLIENTE_H_
#define CLIENTE_H_

#include <gtk/gtk.h>
#include <string>
#include  "common_MSocket.h"
#include  "common_Cambio.h"

#include "common_Parser.h"
#include "common_DocumentoConcurrente.h"
#include "common_MThread.h"
#include  "common_Lista.h"
class Vista;
class Cliente: public MThread{
private:
	std::string nombre;
	MSocket* socket;
	DocumentoConcurrente* documentoConc;
	bool conectado;
	Lista<std::string> listaDeAmigos;
	MMutex mutex;
	const char* puerto;
Vista* vista;

public:
	Cliente();
	void setNombre(std::string nombre);
	std::string getNombre();
	DocumentoConcurrente* getDocumentoConc();
	MSocket*  getSocket();
	Lista<std::string> getAmigos();
	void agregarAmigo(std::string nombre);
	void conectarSocket(const char* IP, const char* puerto);
	void Inicializar(const char* ip,const char* port, GtkWidget* boton);
	void EnviarDatosInicio();
	void EnviarCambio(Cambio cambio);
	void quitarAmigo(std::string nombre);
	void setVista(Vista* vista);
	void Escuchando();
void Desloguearse();
	void setConectado(bool newStatus);
	bool  getConectado();
	void ejecutarAccion(Parser parser);

void* run();
	virtual ~Cliente();
};

#endif /* CLIENTE_H_ */
