/*
 * Cambio.h
 *
 *  Created on: Apr 30, 2009
 *      Author: mmmary
 */


/* Clase que representa a un mensaje que se enviará a través de la red.
 * Tiene diferentes campos separados por comas:
 * N,long,nombre [cambio que envia un cliente cuando desea participar de la edicion]
 * L,long,nombre [el servidor acepta a ese cliente]
 * R,long,nombre [se rechaza el pedido del cliente pues existe otro con el mismo nombre]
 * E,long,nombre [el cliente pide desconectarse]
 * F,long,nombre [un cliente recibe a otro cliente que se acaba de conectar]
 * O,long,nombre [un cliente recibe el nombre de un amigo que se desconecto]
 * D,version,long,contenido [Un cliente recibe el contenido del documento con el número de version del mismo]
 * A,version,alcance,posicion,long,texto [se agregará "texto" en la posicion dentro del contenido del documento.
 * Se indica el número de version sobre el cual se ha realizado dicho cambio.]
 * B,version,alcance,posicion,long,texto [se borrará "texto" en la posicion dentro del contenido del documento.
 * Se indica el número de version sobre el cual se ha realizado dicho cambio.]
 * El numero de alcance:
 * 0:el cambio debe verse reflejado tanto en el documento como en la vista del cliente
 * 1:el cambio debe verse reflejado solo en el documento, NO en la vista del cliente,
 * pues el mismo realizo ese cambio.
 * 2:el cambio debe verse reflejado solo en la vista, NO en el documento; pues se da cuando un cambio
 * que el cliente ha realizado se rechaza, por lo q lo que el ha hecho en la vista no es valido.
 *
 * */
#ifndef CAMBIO_H_
#define CAMBIO_H_

#include <string>

class Cambio {
private:

	std::string tipo;
	int version;
	int alcance;
	int posicion;
	int longitud;
	std::string texto;

	/*representacion del cambio en un string*/
	std::string stdCambio;

public:
/* diferentes constructores, dentro se crea el stdCambio*/
	Cambio();

	Cambio(std::string tipo,  std::string texto);
	Cambio(std::string tipo, int version,  std::string texto);
	Cambio(std::string tipo, int version,int alcance, int posicion, std::string texto);

	bool operator!=(const Cambio& otro)const;
	std::string getStdCambio();
	std::string getTexto();
	int getPosicion();
	std::string getTipo();
	int getVersion();

};

#endif /* CAMBIO_H_ */
