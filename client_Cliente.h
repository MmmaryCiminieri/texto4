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

#include  "common_MSocket.h"
#include  "common_Cambio.h"
#include "common_Parser.h"
#include "common_DocumentoConcurrente.h"
#include "common_MThread.h"
#include  "common_Lista.h"

class Vista;
class Cliente: public MThread {

private:
	std::string nombre;
	MSocket* socket;
	DocumentoConcurrente* documentoConc;
	bool conectado;
	Lista<std::string> listaDeAmigos;
	MMutex mutex;
	const char* puerto;
	Vista* vista;

public:
	/*constructor de la clase*/
	Cliente();

	void setNombre(std::string nombre);
	std::string getNombre();
	DocumentoConcurrente* getDocumentoConc();
	MSocket* getSocket();
	Lista<std::string> getAmigos();
	void setVista(Vista* vista);
	void setConectado(bool newStatus);
		bool getConectado();



	/*Agrego un amigo a mi lista de amigos */
	void agregarAmigo(std::string nombre);

	/*Intento conectar mi socket al servidor, se setea la variable conectado*/
	void conectarSocket(const char* IP, const char* puerto);

	/*Primeramente se intenta conectar al socket, si no puede hacerlo emite una ventana de error
	 * Envío al servidor mi nombre.
	 * Llamo al execute de Cliente.
	 * */
	void Inicializar(const char* ip, const char* port, GtkWidget* boton);

	/*Envío a través de mi socket, al servidor, mi nombre*/
	void EnviarDatosInicio();

	/*Envio un cambio a través del socket, al servidor*/
	void EnviarCambio(Cambio cambio);

	/*remuevo un amigo de mi lista y de la vista*/
	void quitarAmigo(std::string nombre);

	//TODO ver q andeee
	/*se crea un socket que se conecta con mi cliente y le envia un mensaje de deslogueo*/
	void Desloguearse();

	/*según el tipo de cambio recibido desde el servidor,  se ejecutarán diferentes acciones sobre este Cliente,
	 * sus amigos y su documento */
	void ejecutarAccion(Parser parser);

	/*Mientras este conectado el cliente: escucha y procesa cambios*/
	void* run();

	virtual ~Cliente();
};

#endif /* CLIENTE_H_ */
