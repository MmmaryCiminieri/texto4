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
	int version;
	bool cambios;

public:
	Documento();
	Documento(std::string documento);
	void agregarTexto(std::string texto, unsigned int posicion);
	void borrarTexto(std::string texto, int posicion);
	int getVersion();
	bool hayCambios();

	void setVersion(int nro);
	void setContenido(std::string contenido);

	void aumentarVersion();
	std::string getContenido();
	virtual ~Documento();
};

#endif /* DOCUMENTO_H_ */
