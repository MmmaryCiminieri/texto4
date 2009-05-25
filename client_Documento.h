/*
 * Documento.h
 *
 *  Created on: Apr 25, 2009
 *      Author: mmmary
 */

#ifndef DOCUMENTO_H_
#define DOCUMENTO_H_

#include <string>

class Documento {
private:
	std::string contenido;
	int nroVersion;

public:

	Documento();

	Documento(std::string documento, int nroVersion);
	int getVersion();

	void aumentarVersion();
	void setContenido(std::string contenido);
	void setVersion(int nro);
	std::string getContenido();
	void agregarTexto(std::string texto, unsigned int posicion);
	void borrarTexto(std::string texto, int posicion);

	bool hayCambios();
	virtual ~Documento();
};

#endif /* DOCUMENTO_H_ */
