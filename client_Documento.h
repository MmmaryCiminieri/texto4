/*
 * Documento.h
 *
 *  Created on: Apr 25, 2009
 *      Author: mmmary
 */

/* Documento del cliente, tiene un contenido y un número de versión.
 * */

#ifndef DOCUMENTO_H_
#define DOCUMENTO_H_

#include <string>

class Documento {
private:
	std::string contenido;
	int nroVersion;

public:

	Documento();
	Documento(const std::string& documento, int nroVersion);

	int getVersion();
	void aumentarVersion();
	void setContenido(const std::string& contenido);
	void setVersion(int nro);
	std::string getContenido();

	/*se agrega texto en la posición posicion del contenido del documento*/
	void agregarTexto(const std::string& texto, unsigned int posicion);

	/*se borra texto en la posición posicion del contenido del documento*/
	void borrarTexto(const std::string& texto, int posicion);

	virtual ~Documento();
};


#endif /* DOCUMENTO_H_ */
