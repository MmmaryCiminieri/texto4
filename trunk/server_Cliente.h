/*
 * Cliente.h
 *
 *  Created on: Apr 25, 2009
 *      Author: mmmary
 */

#ifndef CLIENTE_H_
#define CLIENTE_H_

#include <string>
#include <gtk/gtk.h>
#include "common_MSocket.h"

#include "server_Servidor.h"
#include "common_MThread.h"
#include "common_Parser.h"
class Cliente : public MThread {

private:
	std::string nombre;
	MSocket* socket;
Servidor* servidor;
bool conectado;




public:
	std::string getNombre();

	void setNombre(std::string nombre);

	Cliente(MSocket* socket, Servidor* servidor);
	 void* run();
		void ingresoUsuario();


		void ejecutarAccion(Parser parser);

	//void setSocket(MSocket* socket);
	MSocket* getSocket();
	virtual ~Cliente();
};

#endif /* CLIENTE_H_ */
