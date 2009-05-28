/*
 * Documento.cpp
 *
 *  Created on: Apr 25, 2009
 *      Author: mmmary
 */

#include <iostream>
#include "server_Documento.h"

Documento::Documento(const std::string& doc) {
	this->version = 1;
 this->contenido = doc;
}

Documento::Documento(){
	this->version = 1;
}

void Documento::agregarTexto(const std::string& texto, unsigned int posicion){
std::string str = texto;
if(posicion <= contenido.size()){
 this->contenido.insert(posicion,str);

}
else{
	int pad = posicion - contenido.size();
			for (int j=0;j<=(pad-1);j++){
				this->contenido = this->contenido.append(" ");

			}
	this->contenido = this->contenido.append(str);

}
std::cout << "el doc: "<<contenido << std::endl;

}

void Documento::aumentarVersion(){
	this->version++;
}

void Documento::borrarTexto(const std::string& texto, int posicion){

int sizeToRemove = texto.size();
this->contenido = this->contenido.erase(posicion, sizeToRemove);
std::cout << "el doc: "<<contenido << std::endl;

}


void Documento::setVersion(int nro) {
	this->version = nro;
}

void Documento::setContenido(const std::string& contenido){

	this->contenido = contenido;


}


int Documento::getVersion(){
	return this->version;
}
std::string Documento::getContenido(){
		return this->contenido;
	}

Documento::~Documento() {
	// TODO Auto-generated destructor stub
}
