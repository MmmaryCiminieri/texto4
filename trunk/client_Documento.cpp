/*
 * Documento.cpp
 *
 *  Created on: Apr 25, 2009
 *      Author: mmmary
 */
#include "iostream"
#include "client_Documento.h"

Documento::Documento(std::string contenido, int nro) {
	this->contenido = contenido;
	this->nroVersion = nro;
}

Documento::Documento(){
	this->nroVersion =0;

}

void Documento::aumentarVersion(){
	this->nroVersion++;
}

std::string Documento::getContenido(){
	return this->contenido;
}
void Documento::setContenido(std::string contenido){
	this->contenido = contenido;
}

int Documento::getVersion() {
	return this->nroVersion;
}

void Documento::setVersion(int nro) {
	this->nroVersion = nro;
}


void Documento::agregarTexto(std::string texto,unsigned int posicion) {

	if(posicion <= contenido.size()){
		/*inserto en el texto*/
		this->contenido = this->contenido.insert(posicion, texto);

	}
	else{
/*debo hacer un append con espacios en el medio*/
		/*teoricamente nunca se da*/
		int pad = posicion - contenido.size();
		for (int j=0;j<=(pad -1);j++){
			this->contenido = this->contenido.append(" ");

		}
		this->contenido = this->contenido.append( texto);
	}
	std::cout << "el doc: "<<contenido << std::endl;

}
void Documento::borrarTexto(std::string texto, int posicion) {

	int sizeToRemove = texto.size();
	this->contenido = this->contenido.erase(posicion, sizeToRemove);
	std::cout << "el doc: "<<contenido << std::endl;

}

Documento::~Documento(){}
