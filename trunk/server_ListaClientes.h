/*
 * ListaClientes.h
 *
 *  Created on: Apr 25, 2009
 *      Author: mmmary
 */

/* Se agrupan todos los usuarios de la aplicación.
 * */

#ifndef LISTACLIENTES_H_
#define LISTACLIENTES_H_

#include "common_Lista.h"
class Cliente;

class ListaClientes {
public:
	Lista<Cliente*>* listaClientes;


public:
	ListaClientes();
	Lista<Cliente*>* getLista();

	/*se remueve un cliente de la lista*/
	bool remover(std::string nombre);

	virtual ~ListaClientes();
};

#endif /* LISTACLIENTES_H_ */
