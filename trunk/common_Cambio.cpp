/*
 * Cambio.cpp
 *
 *  Created on: Apr 30, 2009
 *      Author: mmmary
 */

#include "common_Cambio.h"
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
}
Cambio::Cambio(const std::string& tipo,  const std::string& texto) {
	this->tipo = tipo;
	this->version = INVALIDO;
	this->alcance = INVALIDO;
	this->longitud = texto.size();
	this->texto = texto;
	this->posicion = INVALIDO;
}

Cambio::Cambio(const std::string& tipo, int version,  const std::string& texto) {
	this->tipo = tipo;
	this->version = version;
	this->longitud = texto.size();
	this->texto = texto;
	this->alcance = INVALIDO;
	this->posicion = INVALIDO;
}

bool Cambio::operator!=(const Cambio& otro)const{

	return ((tipo !=otro.tipo)||(version !=otro.version)||(alcance !=otro.alcance) ||(posicion !=otro.posicion)||(longitud !=otro.longitud)||(texto !=otro.texto));
}

int Cambio::getVersion() const {
	return this->version;
}

std::string Cambio::getTexto() const {
	return this->texto;
}

std::string Cambio::getTipo() const {
	return this->tipo;
}

int Cambio::getPosicion() const {
	return this->posicion;
}

int Cambio::getAlcance() const {
	return alcance;
}

int Cambio::getLongitud() const {
		return longitud;
}

std::string Cambio::getStdCambio(){
	Parser parser;
	return parser.toString(*this);
}
