/*
 * Cliente.h
 *
 *  Created on: Apr 25, 2009
 *      Author: mmmary
 */

/*Representación del cliente remoto dentro del servidor.
 * Esta clase es la encargada de las commmuniocaciones desde el cliente, hacia el servidor.
 * */
#ifndef CLIENTE_H_
#define CLIENTE_H_

#include <string>
#include <gtk/gtk.h>

#include "common_MSocket.h"
#include "server_Servidor.h"
#include "common_MThread.h"
#include "common_Parser.h"
class Cliente: public MThread {

private:
	std::string nombre;
	MSocket* socket;
	Servidor* servidor;
	bool conectado;

public:

	Cliente(MSocket* socket, Servidor* servidor);

	std::string getNombre();
	void setNombre(std::string nombre);
	MSocket* getSocket();


	/*Mientras este conectado el cliente: escucha y procesa cambios*/
	void* run();

	/*según el tipo de cambio recibido desde el cliente remoto,  se ejecutarán diferentes acciones sobre este Cliente,
	 * el servidor y el documento */
	void ejecutarAccion(Parser parser);

	virtual ~Cliente();
};

#endif /* CLIENTE_H_ */
