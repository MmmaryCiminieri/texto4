/*
 * ServidorEx.h
 *
 *  Created on: May 17, 2009
 *      Author: mmmary
 */

/* Servidor que se dedica a escuchar las entradas de nuevos clientes.
 * Tiene un puntero al Servidor que es quien luego manejará
 * toda la lógica del documento Concurrente.
 * */


#ifndef SERVIDOREX_H_
#define SERVIDOREX_H_
#include "server_Servidor.h"
#include "common_MSocket.h"

class ServidorEx : public MThread{
private:
	Servidor* servidor;
	MSocket* socket;
	bool isValido;

public:

	ServidorEx(Servidor* servidor);

	/*se escucha, si un cliente se desea conectar lo creo en el heap y se lo envio al servidor*/
	void* run();
	virtual ~ServidorEx();
};

#endif /* SERVIDOREX_H_ */
