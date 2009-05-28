/*
 * Documento.h
 *
 *  Created on: Apr 25, 2009
 *      Author: mmmary
 */


/* Documento del servidor, es el válido para todos los clientes.Tiene un contenido y un número de versión.
 * */

#ifndef DOCUMENTO_H_
#define DOCUMENTO_H_

#include <string>

class Documento {
private:
	std::string contenido;
	int version;


public:

	Documento();
	Documento(const std::string& documento);

	int getVersion();
		//bool hayCambios();
		void setVersion(int nro);
		void setContenido(const std::string& contenido);
		void aumentarVersion();
		std::string getContenido();

		/*se agrega texto en la posición posicion del contenido del documento*/
	void agregarTexto(const std::string& texto, unsigned int posicion);

	/*se borra texto en la posición posicion del contenido del documento*/
	void borrarTexto(const std::string& texto, int posicion);

};

#endif /* DOCUMENTO_H_ */
