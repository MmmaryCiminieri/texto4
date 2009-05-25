/*
 * Vista.h
 *
 *  Created on: Apr 25, 2009
 *      Author: mmmary
 */

#ifndef VISTA_H_
#define VISTA_H_
#include "string"
#include "client_Cliente.h"
#include "client_Ventana.h"

class Vista {
	VentanaIngreso ventana;

public:
	Vista(/*Cliente* cliente*/);
	virtual ~Vista();
	void agregarAmigo(const char* nombre);
	void quitarAmigo(const char* nombre);
	VentanaIngreso* getVentana();
	void cargarDocumento(std::string contenido);
	void mostrar();
	void ErrorConectar();
	void borrar(const char* str, int posicion);
	void agregar(const char* str, int posicion);
	void Actualizar();
};

#endif /* VISTA_H_ */
