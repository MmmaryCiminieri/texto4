/*
 * ListaClientes.h
 *
 *  Created on: Apr 25, 2009
 *      Author: mmmary
 */

#ifndef LISTACLIENTES_H_
#define LISTACLIENTES_H_

#include "common_Lista.h"
class Cliente;

class ListaClientes {
public:
	Lista<Cliente*>* listaClientes;


public:
	ListaClientes();
	//void agregarTexto(std::string texto, int posicion);
	Lista<Cliente*>* getLista();
	bool remover(std::string nombre);
	virtual ~ListaClientes();
};

#endif /* LISTACLIENTES_H_ */
