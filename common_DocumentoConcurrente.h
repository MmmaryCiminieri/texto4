/*
 * DocumentoConcurrente.h
 *
 *  Created on: Apr 25, 2009
 *      Author: mmmary
 */

/*
 * Documento Concurrente es la clase  que para modificar su documento interno se bloquea,
 * así se le puede agregar texto o borrarle manteniendo la validez del mismo.
 * Tiene un Documento, que tiene un número de version
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

	/*se agrega texto en la posicion posicion del documento,
	 * se incrementa el numero de version del mismo*/
	void agregarTexto(const std::string& texto, int offset);

	/*se borra texto en la posicion posicion del documento,
	 * se incrementa el numero de version del mismo*/
	void borrarTexto(const std::string& texto, int offset);

	void aumentarVersion();
	Documento* getDocumento();
	void setDocumento(const std::string& contenido);
	int getVersion();
	void setVersion(int nro);

};

#endif /* DOCUMENTOCONCURRENTE_H_ */
