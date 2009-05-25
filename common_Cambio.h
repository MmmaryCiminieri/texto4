/*
 * Cambio.h
 *
 *  Created on: Apr 30, 2009
 *      Author: mmmary
 */


/* Clase que representa a un mensaje que se enviará a través de la red
 *
 * */
#ifndef CAMBIO_H_
#define CAMBIO_H_

#include <string>

class Cambio {
private:
	std::string tipo;
	int version;
	/*0: para documento y vista; 1:para documento ; 2:para la vista */
	int alcance;
	int posicion;
	int longitud;
	std::string texto;
	/*representacion del cambio en un string*/
	std::string stdCambio;

public:
/*constructores*/
	Cambio(std::string tipo,  std::string texto);
	Cambio(std::string tipo, int version,  std::string texto);
	Cambio(std::string tipo, int version,int alcance, int posicion, std::string texto);


	std::string getStdCambio();
	std::string getTexto();
	int getPosicion();
	std::string getTipo();
	int getVersion();

};

#endif /* CAMBIO_H_ */
