/*
 * VentanaIngreso.h
 *
 *  Created on: Apr 24, 2009
 *      Author: mmmary
 */

#ifndef VENTANAINGRESO_H_
#define VENTANAINGRESO_H_
#include <gtk/gtk.h>

class Cliente;
class Vista;
class VentanaIngreso {
private:
	gulong insertSignal;
	gulong deleteSignal;
	Cliente* cliente;
	Vista* vista;

	GtkWidget* ventana;
	GtkWidget* contenedorV;
	GtkWidget* table;
	GtkWidget* label;
	GtkWidget* label2;
	GtkWidget* label3;
	GtkWidget* label4;
	GtkWidget* label5;
	GtkWidget* entrada;
	GtkWidget* entrada2;
	GtkWidget* entrada3;
	GtkWidget* boton;
	GtkWidget* botonDeslog;
	GtkWidget* contenedor;
	GtkWidget* contenedor2;
	GtkWidget* contenedor3;

	GtkWidget* view;
	GtkTextTagTable * docTagTable;
	GtkTextBuffer* texto;
	GtkWidget* swindow;

	GtkTextTagTable * docTagTable2;
	GtkTextBuffer* lista;
	GtkWidget* view2;
	GtkWidget* swindow2;

public:

	gulong getinsertSignal();

	gulong getdeleteSignal();

	GtkWidget* getVentana();

	void setVista(Vista* vista);
	VentanaIngreso(const VentanaIngreso& ventanaIngreso);
	VentanaIngreso(/*Cliente* cliente*/);
	Cliente* getCliente();
	GtkTextBuffer* getTexto();
	GtkWidget* getView();
	GtkTextBuffer* getLista();


GtkWidget* getBotonDeslog();
	void crearBotonDeslog();
	void crearVentana();
	void crearLabel();
	void crearLabel2();
	void crearLabel3();
	void crearLabel4();
	void crearLabel5();
	void crearBoton();
	void crearEntrada();
	void crearEntrada2();
	void crearEntrada3();
	void crearTable();
	static void on_boton_clicked(GtkWidget *widget, VentanaIngreso* data);


	static void on_boton_clicked_logout(GtkWidget *widget, VentanaIngreso* data);
	void crearCamposVerticales();
	void crearCamposTexto();
	void crearCamposTexto2();
	void crearCamposTexto3();

	void setCliente(Cliente* cliente);

	Vista* getVista();
	void crearTexto();
	void crearLista();
	void mostrar();
	virtual ~VentanaIngreso();
};

#endif /* VENTANAINGRESO_H_ */
