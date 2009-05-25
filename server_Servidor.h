/*
 * Servidor.h
 *
 *  Created on: Apr 25, 2009
 *      Author: mmmary
 */

#ifndef SERVIDOR_H_
#define SERVIDOR_H_

#include "server_ListaClientes.h"
#include "common_DocumentoConcurrente.h"
#include "common_MSocket.h"
#include "common_Cambio.h"
#include "common_Cola.h"
#include "common_MThread.h"


struct NombreCambio{
	std::string nombre;
	Cambio* cambio;

NombreCambio(std::string nombre,Cambio* cambio){
	this->nombre = nombre;
	this->cambio= cambio;
}
NombreCambio(){}

bool operator!=(const NombreCambio& otro)const{
	return ((otro.nombre!=nombre) || (otro.cambio != cambio));

}
};


class Servidor: public MThread {

private:
	Cola<NombreCambio>* colaDeCambios;
	int puerto;
	int cantClientes;
	ListaClientes listaDeClientes;
	DocumentoConcurrente documentoConc;
	MSocket* socket;
	bool escucho;
	MMutex mutex;

public:
	Servidor(unsigned short puerto, int cantClientes);
	ListaClientes* getListaClientes();

	int getPuerto();
	int getCantClientes();

	void cerrarServidor();
	MSocket* getSocket();
	void* run();
	bool getEstado();
	void setEstado(bool estado);
	int getVersion();
	Cola<NombreCambio>* getColaDeCambios();
	DocumentoConcurrente* getDocumentoConc();
	void VerificacionCliente(Cliente* cliente);
	void enviarCambio(Cambio cambio, std::string nombre, int flag);
	void avisarATodos(std::string nombre);
	void crearListaAmigos(Cliente* cliente);
	void agregarCambio(Cambio* cambio, std::string nombre);
	void procesarCambio(Cambio* cambio, std::string nombre);
	void leerCambios();

	virtual ~Servidor();
};

#endif /* SERVIDOR_H_ */
