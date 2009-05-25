/*
 * Parser.h
 *
 *  Created on: May 1, 2009
 *      Author: mmmary
 */


/* Se encarga de interpretar los mensajes recibidos, que son estructuras de tipo Cambio,
 * y  se los  se los divide en diferentes campos.
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
	bool Procesar(const char* buff, int* tamanioBuffer);
	void reset();
	int ProcesarNumero(const char* buffer, int posicion, int* valor,
			int* valorParcial, int tamanioBuffer);

	int getVersion();
	std::string getTexto();
	std::string getTipo();
	int getPosicion();
	int getAlcance();

	Cambio* toCambio();
	virtual ~Parser();

};

#endif /* PARSER_H_ */
