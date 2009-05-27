/*
 * Parser.h
 *
 *  Created on: May 1, 2009
 *      Author: mmmary
 */


/* Clase que se encarga de interpretar los mensajes recibidos, que son estructuras de tipo Cambio,
 * y  se los  se los divide en diferentes campos.
 * De cada campo se tiene un campoParcial, pues el Precesar() puede recibir parte de un mensaje,
 * por lo que a la siguiente iteración deberá saber su estado anterior para interpretar el buffer actual.
 *
 * Ver common_Cambio.h para entender su estructura.
 * */
#ifndef PARSER_H_
#define PARSER_H_

#include "common_Cambio.h"

class Parser {

private:

	std::string tipo;
	bool tipoLeido;
	int version;
	int versionParcial;
	int alcance;
	int alcanceParcial;
	int posicion;
	int posicionParcial;
	int longitud;
	int longitudParcial;
	std::string texto;
	std::string textoParcial;
	bool textoIncompleto;

public:

	Parser();
	int getVersion();
		std::string getTexto();
		std::string getTipo();
		int getPosicion();
		int getAlcance();

	/*Procesa un buffer y retorna true si ha terminado de leer UN cambio,
	 * false si sólo ha leido un mensaje incompleto. tamanioBuffer, al finalizar, tendrá la cantidad de bytes
	 * de buffer procesados.*/
	bool procesar(const char* buff, int* tamanioBuffer);

	/*Se resetean (en cero) los campos del parser para utilizarlo para leer otro cambio.*/
	void reset();

	/*del buffer se debe leer un número (valor y valor parcial). Posición indica al comenzar
	 * desde donde se debe leer dicho número.Retorna la posición dentro del buffer en donde terminó
	 * de leer el número.
	 *   */
	int procesarNumero(const char* buffer, int posicion, int* valor,
			int* valorParcial, int tamanioBuffer);

	/*Se transforman los campos de un parser en un Cambio que contiene todos los campos
	 * posibles, donde si no sirven, valen cero.
	 * OJO, se crea un nuevo Cambio en el heap.
	 * */
	Cambio*  toCambio();

	std::string toString(const Cambio& cambio);

	virtual ~Parser();

};

#endif /* PARSER_H_ */
