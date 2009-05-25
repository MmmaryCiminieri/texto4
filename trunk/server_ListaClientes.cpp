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

//void ListaClientes::agregarTexto(std::string texto, int posicion) {
//	//TODO decirle a todos los cllientes que ha habido un agregado
//	Cliente* clienteAux;
//	Cambio cambio("A", sizeof(texto), texto);
//	Iterador<Cliente*> it = this->listaClientes->iterador();
//	while (it.hasNext()) {
//		clienteAux = it.next();
//		MSocket* socketCliente = clienteAux->getSocket();
//		socketCliente->send(cambio.getStdCambio(), sizeof(cambio.getStdCambio()));
//
//	}
//
//
////}
//
//void ListaClientes::quitarTexto(std::string texto, int posicion) {
//	//TODO igual AL ANTERIOR
//	Cliente* clienteAux;
//	Cambio cambio("B", sizeof(texto), texto);
//	Iterador<Cliente*> it= this->listaClientes->iterador();
//	while(it.hasNext()) {
//		clienteAux = it.next();
//		MSocket* socketCliente = clienteAux->getSocket();
//		socketCliente->send(cambio.getStdCambio(), sizeof(cambio.getStdCambio()));
//	}
//}

ListaClientes::~ListaClientes() {

	std::cout<< "destructor de lista clientes "<<std::endl;

	}
