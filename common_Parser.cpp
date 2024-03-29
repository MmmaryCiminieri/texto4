/*
 * Parser.cpp
 *
 *  Created on: May 1, 2009
 *      Author: mmmary
 */
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <string.h>
#include "common_Parser.h"

#define MAXLONG 20
#define TAMANIIO  1024

Parser::Parser() {

	this->tipo = 'Z';
	this->tipoLeido = false;
	this->version = 0;
	this->versionParcial = 0;
	this->alcance = 0;
	this->alcance = 0;
	this->posicionParcial = 0;
	this->posicion = 0;
	this->longitudParcial = 0;
	this->longitud = 0;
	this->textoIncompleto = true;
}

int Parser::getAlcance() {
	return this->alcance;
}
int Parser::procesarNumero(const char* buffer, int actual, int* valor,
		int* valorParcial, int tamanioBuffer) {

	char cAux = '.';
	int i = actual;
	int c = 0;

	if ((*valorParcial) == 0) {
		/*es la primera vez que leo caracteres del valor*/
		c = 0;
	} else {
		/*he leido la longitud de manera incompleta*/
		c = (*valorParcial);
	}

	while ((cAux != ',') && (i <= tamanioBuffer)) {

		cAux = buffer[i];
		c = c * 10 + atoi(&cAux);
		cAux = buffer[i + 1];
		i++;
	}
	if (cAux == ',') {
		/*lei la longitud completa*/
		(*valor) = c;

	} else {
		/*Aun no la termine de leer*/
		(*valorParcial) = c;
	}
	return i;
}

int menor(int a, int b) {
	if (a > b)
		return b;
	return a;
}

void Parser::reset() {
	this->tipo = 'Z';
	this->tipoLeido = false;
	this->version = 0;
	this->versionParcial = 0;
	this->posicion = 0;
	this->posicionParcial = 0;
	this->alcance = 0;
	this->alcanceParcial = 0;
	this->longitudParcial = 0;
	this->longitud = 0;
	this->textoIncompleto = true;
	this->texto.erase(0, texto.size());
}

bool Parser::procesar(const char* buffer, int* tamaniio) {

	if (*tamaniio == 0) {
		return false;
	}
	int actual = 0;
	int tamanioBuffer = *tamaniio;
	if (!this->tipoLeido) {
		/*aun no lei el tipo*/
		this->tipo = buffer[actual];
		actual++;
		/*leo la coma*/
		actual++;
		this->tipoLeido = true;
	}
	*tamaniio = actual;
	if (actual >= tamanioBuffer) {
		return false;
	}

	if (((this->tipo == "A") || (this->tipo == "B") || (this->tipo == "D"))
			&& (this->version == 0)) {
		/* debo analizar el numero de version*/

		/*No he leido el numero de version en su totalidad, o ni siquiera he comenzado*/
		actual = this->procesarNumero(buffer, actual, &version,
				&versionParcial, tamanioBuffer);

		actual++;
		/*he leido pero el buffer es menor*/
		*tamaniio = actual;
		if (actual >= tamanioBuffer) {
			return false;
		}
	}
	if (((this->tipo == "A") || (this->tipo == "B")) && (this->alcance == 0)) {
		/* debo analizar el alcance*/
		/*No he leido el numero de version en su totalidad, o ni siquiera he comenzado*/
		actual = this->procesarNumero(buffer, actual, &alcance,
				&alcanceParcial, tamanioBuffer);

		actual++;
		/*he leido pero el buffer es menor*/
		*tamaniio = actual;
		if (actual >= tamanioBuffer) {
			return false;
		}
	}

	if (((this->tipo == "A") || (this->tipo == "B")) &&(this->posicion == 0)) {
		/*debo analizar la posicion en donde hacer el cambio*/

			/*No he leido la longitud en su totalidad, o ni siquiera he comenzado*/
			actual = this->procesarNumero(buffer, actual, &posicion,
					&posicionParcial, tamanioBuffer);
		/*he leido pero el buffer es menor*/
						*tamaniio = actual;
			if (actual >= tamanioBuffer) {
				return false;
			}

		}


	if (this->longitud == 0) {
		/*No he leido la longitud en su totalidad, o ni siquiera he comenzado*/
		actual = this->procesarNumero(buffer, actual, &longitud,
				&longitudParcial, tamanioBuffer);
		/*he leido pero el buffer es menor*/
					*tamaniio = actual;
		if (actual >= tamanioBuffer) {
			return false;
		}

	}

	if (this->textoIncompleto) {

		if (this->longitud != 0) {

			/*termine de leer la longitud  y ahora leerÃ©*/
			char* ctexto = new char[tamanioBuffer];
			bzero(ctexto, tamanioBuffer);
			int j = 0;
			char cAux = '.';

			/*este uno y los  i++ de los while */
			int cantidadLeida = ++actual;

			int min = menor(this->longitud, tamanioBuffer - cantidadLeida);

			for (int k = 1; k <= min; k++) {
				ctexto[j] = buffer[actual];
				cAux = buffer[actual + 1];
				actual++;
				j++;
			}

			this->texto.append(ctexto);
			actual++;
			delete[] ctexto;
			if (this->longitud > (tamanioBuffer - cantidadLeida)) {
				/*no he leido por completo, falta informacion*/
				*tamaniio = actual;
				return false;

			} else {
				this->textoIncompleto = false;
				*tamaniio = --actual;
				if (actual == 0) {
					return false;
				}
				return true;

			}

		}
	}

	*tamaniio = --actual;
	if (actual == 0) {
		return false;
	}

	return true;
}

std::string Parser::getTexto() {
	return this->texto;
}

std::string Parser::getTipo() {
	return this->tipo;
}

std::string Parser::toString(const Cambio& cambio) {

	std::string str;
	/*me crea un string de un cambio, separado por comas*/
	str = cambio.getTipo();
	str.append(",");
	char slong1[MAXLONG];
	if (cambio.getVersion() != Cambio::INVALIDO) {
		sprintf(slong1, "%d", cambio.getVersion());
		str.append(slong1);
		str.append(",");
	}
	if (cambio.getAlcance() != Cambio::INVALIDO) {
		sprintf(slong1, "%d", cambio.getAlcance());
		str.append(slong1);
		str.append(",");
	}
	if (cambio.getPosicion() != Cambio::INVALIDO) {

		sprintf(slong1, "%d", cambio.getPosicion());
		str.append(slong1);
		str.append(",");
	}
	char slong[MAXLONG];
	sprintf(slong, "%d", cambio.getLongitud());
	str.append(slong);
	str.append(",");
	str.append(cambio.getTexto());

	return str;

}

Cambio* Parser::toCambio() {
	Cambio* cambio = new Cambio(tipo, version, alcance, posicion, texto);
	return cambio;
}

int Parser::getVersion() {
	return this->version;
}

int Parser::getPosicion() {
	return this->posicion;
}

Parser::~Parser() {
}
