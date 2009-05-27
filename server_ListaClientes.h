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
#include <list>
#include <string>

class Cliente;

class ListaClientes {
public:
	std::list<Cliente*> listaClientes;


public:

	std::list<Cliente*>& getLista();

	/*se remueve un cliente de la lista*/
	void remover(std::string nombre);

};

#endif /* LISTACLIENTES_H_ */
