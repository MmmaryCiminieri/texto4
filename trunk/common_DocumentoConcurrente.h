/*
 * DocumentoConcurrente.h
 *
 *  Created on: Apr 25, 2009
 *      Author: mmmary
 */

/*
 * Documento que para modificarse se bloquea,
 * así se le puede agregar texto o borrarle.
 * tiene un documento, que tiene un número de version
 * */
#ifndef DOCUMENTOCONCURRENTE_H_
#define DOCUMENTOCONCURRENTE_H_

#include "common_MMutex.h"
#include "server_Documento.h"
#include "client_Documento.h"
#include <string>

class DocumentoConcurrente {
private:


	Documento documento;
	MMutex mutex;


public:

	DocumentoConcurrente();
	void agregarTexto(std::string texto,int offset);
	void borrarTexto(std::string texto, int offset);

	void aumentarVersion();

	Documento* getDocumento();
	void setDocumento(std::string contenido);
	int getVersion();
	void  setVersion(int nro);

	~DocumentoConcurrente();
};

#endif /* DOCUMENTOCONCURRENTE_H_ */
