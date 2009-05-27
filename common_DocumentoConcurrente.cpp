/*
 * DocumentoConcurrente.cpp
 *
 *  Created on: Apr 25, 2009
 *      Author: mmmary
 */

#include "common_DocumentoConcurrente.h"
#include "common_Lock.h"
#include  <string.h>
#include <iostream>

void DocumentoConcurrente::aumentarVersion(){
	this->documento.aumentarVersion();
}


void DocumentoConcurrente::agregarTexto(const std::string& texto, int posicion) {
Lock lock(this->mutex);
	this->aumentarVersion();
	this->documento.agregarTexto(texto, posicion);

}

void DocumentoConcurrente::borrarTexto(const std::string& texto, int offset) {
	Lock lock(this->mutex);
	this->aumentarVersion();
	this->documento.borrarTexto(texto, offset);
}

void  DocumentoConcurrente::setVersion(int nro){
Lock lock(this->mutex);
	 this->documento.setVersion(nro);
}

Documento* DocumentoConcurrente::getDocumento() {
	Lock lock(this->mutex);
	return &documento;
}

void DocumentoConcurrente::setDocumento(const std::string& contenido) {
Lock lock(this->mutex);
 this->documento.setContenido(contenido);
}
int DocumentoConcurrente::getVersion() {
	Lock lock(this->mutex);
	return this->documento.getVersion();
}


