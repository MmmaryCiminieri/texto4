/*
 * Cambio.cpp
 *
 *  Created on: Apr 30, 2009
 *      Author: mmmary
 */

#include "common_Cambio.h"
//borrar
#include "common_Parser.h"
#include <cstdlib>

int Cambio::INVALIDO = -1;

Cambio::Cambio(){}

Cambio::Cambio(const std::string& tipo, int version,int alcance, int posicion, const std::string& texto) {
	this->tipo = tipo;
	this->version = version;
	this->longitud = texto.size();
	this->texto = texto;
	this->posicion = posicion;
	this->alcance= alcance;
//
//	/*me crea un string de todo lo anterior, separado por comas*/
//	this->stdCambio = tipo;
//	this->stdCambio.append(",");
//	char slong1[MAXLONG];
//	sprintf(slong1, "%d", version);
//	this->stdCambio.append(slong1);
//	this->stdCambio.append(",");
//
//	sprintf(slong1, "%d", alcance);
//	this->stdCambio.append(slong1);
//	this->stdCambio.append(",");
//	sprintf(slong1, "%d", posicion);
//	this->stdCambio.append(slong1);
//	this->stdCambio.append(",");
//	char slong[MAXLONG];
//	sprintf(slong, "%d", longitud);
//	this->stdCambio.append(slong);
//	this->stdCambio.append(",");
//	this->stdCambio.append(texto);

}
Cambio::Cambio(const std::string& tipo,  const std::string& texto) {
	this->tipo = tipo;
	this->version = INVALIDO;
	this->alcance = INVALIDO;
	this->longitud = texto.size();
	this->texto = texto;
	this->posicion = INVALIDO;

//	/*me crea un string de todo lo anterior, separado por comas*/
//	this->stdCambio = tipo;
//	this->stdCambio.append(",");
//	char slong[MAXLONG];
//	sprintf(slong, "%d", longitud);
//	this->stdCambio.append(slong);
//	this->stdCambio.append(",");
//	this->stdCambio.append(texto);

}

Cambio::Cambio(const std::string& tipo, int version,  const std::string& texto) {
	this->tipo = tipo;
	this->version = version;
	this->longitud = texto.size();
	this->texto = texto;
	this->alcance = INVALIDO;
	this->posicion = INVALIDO;

//	/*me crea un string de todo lo anterior, separado por comas*/
//	this->stdCambio = tipo;
//	this->stdCambio.append(",");
//	char slong1[MAXLONG];
//	sprintf(slong1, "%d", version);
//	this->stdCambio.append(slong1);
//	this->stdCambio.append(",");
//	char slong[MAXLONG];
//	sprintf(slong, "%d", longitud);
//	this->stdCambio.append(slong);
//	this->stdCambio.append(",");
//	this->stdCambio.append(texto);

}

bool Cambio::operator!=(const Cambio& otro)const{

	return ((tipo !=otro.tipo)||(version !=otro.version)||(alcance !=otro.alcance) ||(posicion !=otro.posicion)||(longitud !=otro.longitud)||(texto !=otro.texto));
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

	//Parser parser;
	//return parser.toString(*this);

	std::string str;
	/*me crea un string de todo lo anterior, separado por comas*/
		str = tipo;
		str.append(",");
		char slong1[20];
		if(version != INVALIDO){
		sprintf(slong1, "%d", version);
		str.append(slong1);
		str.append(",");
		}
		if(alcance != INVALIDO){
		sprintf(slong1, "%d", alcance);
		str.append(slong1);
		str.append(",");
		}
		if(posicion != INVALIDO){

		sprintf(slong1, "%d", posicion);
		str.append(slong1);
		str.append(",");
		}
		char slong[20];
		sprintf(slong, "%d", longitud);
		str.append(slong);
		str.append(",");
		str.append(texto);

	return str;
}

