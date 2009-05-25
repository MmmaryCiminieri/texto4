/*
 * ListaClientes.cpp
 *
 *  Created on: Apr 25, 2009
 *      Author: mmmary
 */

#include "server_ListaClientes.h"
#include "common_Cambio.h"
//#include "Iterador.h"
#include "server_Cliente.h"

ListaClientes::ListaClientes() {
	this->listaClientes = new Lista<Cliente*> ;

}

 bool ListaClientes::remover(std::string nombre){
	bool retorno = false;
	 Iterador<Cliente*> it= listaClientes->iterador();
	Cliente* cliente;
	while(it.hasNext()){
		cliente = it.next();
		if(cliente->getNombre() == nombre){
			retorno = listaClientes->remove(cliente);
		}
	}
return retorno;
}


Lista<Cliente*>* ListaClientes::getLista(){
	return this->listaClientes;
	}

ListaClientes::~ListaClientes() {
	std::cout<< "destructor de lista clientes "<<std::endl;

	}
