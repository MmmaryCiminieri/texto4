/*
 * Vista.h
 *
 *  Created on: Apr 25, 2009
 *      Author: mmmary
 */

/* Clase que contiene una ventana, a la cual le agrega/texto texto, manejándo las señales de
 * agregar/borrar.
 * */

#ifndef VISTA_H_
#define VISTA_H_
#include "string"
#include "client_Cliente.h"
#include "client_Ventana.h"

class Vista {
	VentanaIngreso ventana;

public:
	Vista();
	VentanaIngreso* getVentana();

	/*agrego un amigo a la ventana donde se ancuentran los mismos*/
	void agregarAmigo(const std::string& nombre);

	/*quito un amigo de la ventana de amigos*/
	void quitarAmigo(const char* nombre);

	/*cargo el contenido a la ventana de texto a editar*/
	void cargarDocumento(const std::string& contenido);

	/*muetro la ventana*/
	void mostrar();

	/*cuando se retira un usuario, la lista (vista) se actualiza*/
	void refrescarLista();

	/*si no se puede conectar el socket al server, muestro una ventana de error */
	void errorConectar();

	/*borro texto en la posicion posicion de la ventana donde se encuentra el documento a editar*/
	void borrar(const char* str, int posicion);

	/*agrego texto en la posicion posicion de la ventana donde se encuentra el documento a editar*/
	void agregar(const char* str, int posicion);

	virtual ~Vista();
};

#endif /* VISTA_H_ */
