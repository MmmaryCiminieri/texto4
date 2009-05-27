/*
 * Servidor.h
 *
 *  Created on: Apr 25, 2009
 *      Author: mmmary
 */

/* Clase que maneja la edición del texto, atendiendo a los usuarios que lo modifican.
 * Esta va recibiendo cambios que acola para luego procesar y avisarle a todos los usuarios conectados
 * de dicho cambio.
 *
 * */

#ifndef SERVIDOR_H_
#define SERVIDOR_H_
#include <list>
#include <queue>
#include "common_DocumentoConcurrente.h"
#include "server_Cliente.h"
#include "common_MSocket.h"
#include "common_Cambio.h"
#include "common_MThread.h"

/*Estructura utilitaria que agrupa un cambio y un nombre, para poder así
 * determinar quién realizó dicho cambio.*/
struct NombreCambio {
	std::string nombre;
	Cambio* cambio;

	NombreCambio() {
	}

	NombreCambio(std::string nombre, Cambio* cambio) {
		this->nombre = nombre;
		this->cambio = cambio;
	}

	bool operator!=(const NombreCambio& otro) const {
		return ((otro.nombre != nombre) || (otro.cambio != cambio));

	}
};

class Servidor: public MThread {

private:

	std::queue<NombreCambio> colaDeCambios;
	int puerto;
	int cantClientes;
	std::list<Cliente*> listaDeClientes;
	DocumentoConcurrente documentoConc;
	MSocket* socket;
	bool escucho;
	MMutex mutex;

	void removerCliente(const std::string& nombre);

public:
	Servidor(unsigned short puerto, int cantClientes);

	std::list<Cliente*>* getListaClientes();
	int getPuerto();
	int getCantClientes();
	bool getEstado();
	void setEstado(bool estado);
	int getVersion();
	std::queue<NombreCambio> getColaDeCambios();
	DocumentoConcurrente* getDocumentoConc();
	MSocket* getSocket();

	/*se setea por consola el puerto donde se oirán a los clientes*/
	//unsigned short setPuerto();

	/*el servidor cambia su estado a no escuchando y hace join de todos
	 * sus clientes*/
	void cerrarServidor();

	/*mientras esté conectado se procesan los cambios acolados por los clientes
	 * en la cola de cambios (si los hay)*/
	void* run();

	/*Se analiza si el cliente que ha requerido conexión tiene el mismo nombre que otro ya conectado:
	 * si es así, se le envia un mensaje : "R,long,nombre" para indicarle que ha sido rechazado.
	 * Si no, se le enviá un mensaje de que se lo ha aceptado "L,long,nombre" ;el documento actual en otro cambio
	 * y se les avisa a todos los usuarios que un cliente se conectó.
	 * */
	void verificacionCliente(Cliente* cliente);

	/*Se envia un Cambio. Nombre indica cual fue el cliente que lo envió al servidor.
	 * Si el flag es cero es por que el cambio se envia a todos. Si es uno, sólo se envía al cliente que lo propuso
	 * pues así le puedo avisar que el cambio propuesto ha sido rechazado.*/
	void enviarCambio(Cambio cambio,const  std::string& nombre, int flag);

	/*Se envía un mensaje a todos los usuarios avisándoles que un amigo se ha conectado*/
	void notificarAmigoConectado(const std::string& nombre);

	/*Cuando un usuario se conecta se le envían los nombres de todos sus amigos
	 * que están conectados*/
	void crearListaAmigos(Cliente* cliente);

	/*se crea una estructura nombreCambio y se la acola a la cola de cambios, donde espera a ser procesada*/
	void agregarCambio(Cambio* cambio, const std::string & nombre);

	/* Con el cambio recibido se ejecutan las acciones sobre el documento y/o sobre
	 * los clientes*/
	void procesarCambio(Cambio* cambio, const std::string& nombre);

	/*Se lee un cambio de la cola, si el cambio tiene el mismo número de version que el documento
	 * actual, se lo procesa; si no se le avisa al cliente que su cambio ha sido rechazado
	 * (por lo que ddeberá modificar su vista). se hace delete del cambio creado en parser.toCambio()
	 * */
	void leerCambios();

	/*Se  llama a desloguearCliente(), join, se lo remueve de la lista y se hace delete del mismo*/
	void desconectarCliente(const std::string& nombre);

	virtual ~Servidor();
};

#endif /* SERVIDOR_H_ */
