/*
 * Cambio.cpp
 *
 *  Created on: Apr 30, 2009
 *      Author: mmmary
 */

#define MAXLONG 20
#include "common_Cambio.h"
#include <cstdlib>

Cambio::Cambio(std::string tipo, int version,int alcance, int posicion, std::string texto) {
	this->tipo = tipo;
	this->version = version;
	this->longitud = texto.size();
	this->texto = texto;
	this->posicion = posicion;
this->alcance= alcance;

	/*me crea un string de todo lo anterior, separado por comas*/
	this->stdCambio = tipo;
	this->stdCambio.append(",");
	char slong1[MAXLONG];
	sprintf(slong1, "%d", version);
	this->stdCambio.append(slong1);
	this->stdCambio.append(",");

	sprintf(slong1, "%d", alcance);
	this->stdCambio.append(slong1);
	this->stdCambio.append(",");
	sprintf(slong1, "%d", posicion);
	this->stdCambio.append(slong1);
	this->stdCambio.append(",");
	char slong[MAXLONG];
	sprintf(slong, "%d", longitud);
	this->stdCambio.append(slong);
	this->stdCambio.append(",");
	this->stdCambio.append(texto);

}
Cambio::Cambio(std::string tipo,  std::string texto) {
	this->tipo = tipo;
	this->longitud = texto.size();
	this->texto = texto;
	this->posicion = posicion;

	/*me crea un string de todo lo anterior, separado por comas*/
	this->stdCambio = tipo;
	this->stdCambio.append(",");
	char slong[MAXLONG];
	sprintf(slong, "%d", longitud);
	this->stdCambio.append(slong);
	this->stdCambio.append(",");
	this->stdCambio.append(texto);

}

Cambio::Cambio(std::string tipo, int version,  std::string texto) {
	this->tipo = tipo;
	this->version = version;
	this->longitud = texto.size();
	this->texto = texto;
	this->posicion = posicion;

	/*me crea un string de todo lo anterior, separado por comas*/
	this->stdCambio = tipo;
	this->stdCambio.append(",");
	char slong1[MAXLONG];
	sprintf(slong1, "%d", version);
	this->stdCambio.append(slong1);
	this->stdCambio.append(",");
	char slong[MAXLONG];
	sprintf(slong, "%d", longitud);
	this->stdCambio.append(slong);
	this->stdCambio.append(",");
	this->stdCambio.append(texto);

}


int Cambio::getVersion(){
	return this->version;
}

std::string Cambio::getTexto(){
	return this->texto;
}
std::string Cambio::getTipo(){
	return this->tipo;
}
int Cambio::getPosicion(){
	return this->posicion;
}

std::string Cambio::getStdCambio() {
	return this->stdCambio;
}

