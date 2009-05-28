/*
 * VentanaIngreso.h
 *
 *  Created on: Apr 24, 2009
 *      Author: mmmary
 */

/*Esta es la ventana mediante la cual el cliente editará el texto.
 *
 * */
#ifndef VENTANAINGRESO_H_
#define VENTANAINGRESO_H_

#include <gtk/gtk.h>

class Cliente;
class Vista;

class VentanaIngreso {
private:

	/*señales de cambios en el texto de la vista*/
	gulong insertSignal;
	gulong deleteSignal;

	/*el cliente al que le pertenece esta ventana*/
	Cliente* cliente;

	Vista* vista;

	/*la ventana y sus contenedores*/
	GtkWidget* ventana;
	GtkWidget* contenedorV;
	GtkWidget* table;
	GtkWidget* contenedor;
	GtkWidget* contenedor2;
	GtkWidget* contenedor3;

	/*labels*/
	GtkWidget* labelNombre;
	GtkWidget* labelIP;
	GtkWidget* labelPort;
	GtkWidget* labelTexto;
	GtkWidget* labelLista;

	/*entradas: text entrys*/
	GtkWidget* entradaNombre;
	GtkWidget* entradaIP;
	GtkWidget* entradaPort;

	/*boton de conectarse*/
	GtkWidget* boton;
	/*boton de desloguearse*/
	GtkWidget* botonDeslog;

	/*campo del documento a editar*/
	GtkWidget* view;
	GtkTextTagTable * docTagTable;
	GtkTextBuffer* texto;
	GtkWidget* swindow;

	/*campo de la lista de amigos conectados*/
	GtkTextTagTable * docTagTable2;
	GtkTextBuffer* lista;
	GtkWidget* view2;
	GtkWidget* swindow2;

	/*Creadores de los GtkWidgets que los crea y los inserta dentro de la ventana*/
	void crearBotonDeslog();
	void crearVentana();
	void crearLabel4();
	void crearLabel5();
	void crearBoton();
	void crearTable();
	void crearCamposVerticales();
		void crearCamposTexto();
		void crearCamposTexto2();
		void crearCamposTexto3();
		/*constructor copia*/
			VentanaIngreso(const VentanaIngreso& ventanaIngreso);



public:

/*creo todos los widgets y los meto dentro de la ventana*/
	VentanaIngreso();


	gulong getinsertSignal();
	gulong getdeleteSignal();
	GtkWidget* getVentana();
	void setVista(Vista* vista);
	Cliente* getCliente();
	GtkTextBuffer* getTexto();
	GtkWidget* getView();
	GtkTextBuffer* getLista();
	GtkWidget* getBotonDeslog();
	void setCliente(Cliente* cliente);
	Vista* getVista();
	bool hayClienteConectado();
	void bloquearBotonDeslog();


	/*el cliente envia un msj de que se va, lo vuelve a recibir para debloquear el recv
		 * se cierra el socket y se hace join. Se usa cuando el cliente se desloguea o se cierra la
		 * ventana*/
		void desloguearCliente();



	/*Cuando uno presina el boton de conectarse, se crea un cliente y  se llama al inicializar del mismo*/
	static void on_boton_clicked(GtkWidget *widget, VentanaIngreso* data);

	/*Cuando uno presina el boton de desloguearse,el cliente le avisa
	 * al servidor que se ha desloguaeado, su estado pasa a ser desconectado y se hace el join del mismo */
		static void	on_boton_clicked_logout(GtkWidget *widget, VentanaIngreso* data);

		/*se crea la scrolled window en  donde se editará en texto y se conectan las señales de agregado y borrado por teclado*/
	void crearTexto();

	/*se crea la lista de amigos*/
	void crearLista();

	/*se muestra la ventana*/
	void mostrar();

	virtual ~VentanaIngreso();
};

#endif /* VENTANAINGRESO_H_ */
