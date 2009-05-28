/*
 * Cliente.h
 *
 *  Created on: May 3, 2009
 *      Author: mmmary
 */

/* Clase que representa a un cliente, que tiene un nombre con el cual se identifica.
 * Este cliente se conecta a un servidor mediante un socket.
 * Un cliente tiene amigos conectados quienes podran modificar el texto.
 * La vista es la interfaz gráfica que maneja a esta clase, poniendo en evidencia los cambios
 * realizados tanto por el cliente como también por sus amigos.
 *
 * */
#ifndef CLIENTE_H_
#define CLIENTE_H_

#include <gtk/gtk.h>
#include <string>
#include <list>

#include  "common_MSocket.h"
#include  "common_Cambio.h"
#include "common_Parser.h"
#include "common_DocumentoConcurrente.h"
#include "common_MThread.h"

class Vista;
class Cliente: public MThread {

private:
	std::string nombre;
	MSocket* socket;
	DocumentoConcurrente* documentoConc;
	bool conectado;
	bool aceptado;
	std::list<std::string> listaDeAmigos;
	MMutex mutex;
	const char* puerto;
	Vista* vista;

	/*Envío a través de mi socket, al servidor, mi nombre*/
		void enviarDatosInicio();

public:
	/*constructor de la clase*/
	Cliente();

	void setNombre(const std::string& nombre);
	std::string getNombre();
	DocumentoConcurrente* getDocumentoConc();
	MSocket* getSocket();
	std::list<std::string> getAmigos();
	void setVista(Vista* vista);
	void setConectado(bool status);
	bool getConectado();
	bool isAceptado();
	void setAceptado(bool status);


	/*Agrego un amigo a mi lista de amigos */
	void agregarAmigo(const std::string& nombre);

	/*Intento conectar mi socket al servidor, se setea la variable conectado*/
	void conectarSocket(const char* IP, const char* puerto);

	/*Primeramente se intenta conectar al socket, si no puede hacerlo emite una ventana de error
	 * Envío al servidor mi nombre.
	 * Llamo al execute de Cliente.
	 * */
	void inicializar(const char* ip, const char* port, GtkWidget* boton);

	/*Envio un cambio a través del socket, al servidor*/
	void enviarCambio(const Cambio& cambio);

	/*remuevo un amigo de mi lista y de la vista*/
	void quitarAmigo(const std::string& nombre);

	/*se crea un socket que se conecta con mi cliente y le envia un mensaje de deslogueo*/
	void desloguearse();

	/*según el tipo de cambio recibido desde el servidor,  se ejecutarán diferentes acciones sobre este Cliente,
	 * sus amigos y su documento */
	void ejecutarAccion(Parser parser);

	/*Mientras este conectado el cliente: escucha y procesa cambios*/
	void* run();

	virtual ~Cliente();
};

#endif /* CLIENTE_H_ */
