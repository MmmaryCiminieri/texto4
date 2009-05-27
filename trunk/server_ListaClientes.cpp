/*
 * ListaClientes.cpp
 *
 *  Created on: Apr 25, 2009
 *      Author: mmmary
 */

#include "server_ListaClientes.h"
#include "common_Cambio.h"
#include "server_Cliente.h"


void ListaClientes::remover(std::string nombre){
	 std::list<Cliente*>::iterator it;
Cliente* clienteAux;
	 for( it = listaClientes.begin(); it != listaClientes.end(); ++it ) {
	       clienteAux = *it;
	       if(clienteAux->getNombre() == nombre){
	       			listaClientes.remove(clienteAux);
	       			return;
	       		}
	     }
}


std::list<Cliente*>& ListaClientes::getLista(){
	return this->listaClientes;
	}


