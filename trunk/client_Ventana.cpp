/*
 * VentanaIngreso.cpp
 *
 *  Created on: Apr 24, 2009
 *      Author: mmmary
 */


#include "client_Ventana.h"
#include "client_Vista.h"
#include "client_Cliente.h"
#include <string>
#include <iostream>



gulong VentanaIngreso::getinsertSignal() {
	return this->insertSignal;
}
gulong VentanaIngreso::getdeleteSignal() {
	return this->deleteSignal;
}
void VentanaIngreso::setCliente(Cliente* cliente){
	this->cliente = cliente;
}


void VentanaIngreso::setVista(Vista* vista){
	this->vista = vista;
}

Vista* VentanaIngreso::getVista(){
	return vista;
}
/* Función 'callback' para atender la señal "clicked" del botón */
void VentanaIngreso::on_boton_clicked(GtkWidget *widget, VentanaIngreso* data) {
	std::cout << "[recibido el evento clicked]" << std::endl;

	/* muestro el contenido de la entrada de texto */
	std::cout << "Texto ingresado de Usuario:" << gtk_entry_get_text(GTK_ENTRY(
			data->entrada)) << std::endl;
//todo borrar
	Cliente* cliente = new Cliente;
	data->setCliente(cliente);
	cliente->setVista(data->getVista());


	data->cliente->setNombre(gtk_entry_get_text(GTK_ENTRY(data->entrada)));
	   //const char* ip = gtk_entry_get_text(GTK_ENTRY(data->entrada2));
	   //const char* port =  gtk_entry_get_text(GTK_ENTRY(data->entrada3));
const char* ip = "127.0.0.1";
const char* port = "8080";
/*trabo el boton*/
gtk_widget_set_sensitive(widget, false);
gtk_widget_set_sensitive(data->botonDeslog, true);

data->cliente->Inicializar(ip, port, widget);

	std::cout << "SALI DEL CLICK" << std::endl;

}

void VentanaIngreso::on_boton_clicked_logout(GtkWidget *widget, VentanaIngreso* data){
	/*el cliente ha decido desloguarse*/
	std::cout << "el cli" <<
data->cliente->getNombre()<< std::endl;
	//data->cliente->Desloguearse();
	//data->cliente->join();
	std::cout << "Termino de joinear" << std::endl;
	//delete data->cliente;

	//data->cliente = NULL;

	gtk_widget_set_sensitive(data->boton,true);
	gtk_widget_set_sensitive(data->botonDeslog, false);
	std::cout << "seteo botones" << std::endl;


}

GtkWidget* VentanaIngreso::getBotonDeslog(){
	return botonDeslog;
}

/* Función 'callback' para atender la señal del evento "delete_event" */
static gboolean on_delete_event(GtkWidget *widget, GdkEvent *event,
		VentanaIngreso* data) {
	std::cout << "[recibido el evento delete_event]" << std::endl;
	std::cout << "el cli" << data->getCliente()->getNombre()<< std::endl;
	return FALSE;
}

GtkWidget* VentanaIngreso::getVentana() {
	return ventana;
}
/* Función 'callback' para atender la señal "destroy" de la ventana. */
static void destruir(GtkWidget *widget,VentanaIngreso* data) {
	std::cout << "[recibido el evento destroy]" << std::endl;
	/* finaliza el loop de gtk_main() y libera memoria */
			gtk_main_quit();
}


VentanaIngreso::VentanaIngreso(/*Cliente* cliente*/) {
	std::cout << "////Constructor VentanaIngreso/////" << std::endl;

//	this->cliente = cliente;

	this->crearVentana();

	this->crearCamposVerticales();
	this->crearTable();

	this->crearLabel();
	this->crearEntrada();
	this->crearLabel2();
	this->crearEntrada2();
	this->crearBotonDeslog();

	this->crearLabel3();
	this->crearEntrada3();
	this->crearBoton();
	this->crearCamposTexto3();

	this->crearLabel4();
	this->crearLabel5();
	this->crearCamposTexto();

	this->crearTexto();
	this->crearLista();
	this->crearCamposTexto2();

}

GtkTextBuffer* VentanaIngreso::getTexto() {

	return this->texto;
	//return gtk_text_view_get_buffer(GTK_TEXT_VIEW(this->view));
}

GtkTextBuffer* VentanaIngreso::getLista() {
	return lista;
}

void VentanaIngreso::crearCamposVerticales() {
	/* creo un contenedor que divide horizontalmente para poner mis widgets
	 * TRUE es para que todos los elementos sean de igual tamaño
	 * 10 es para que deje 10 píxels entre los elementos */
	contenedorV = NULL;
	contenedorV = gtk_vbox_new(TRUE, 10);
	gtk_container_add(GTK_CONTAINER(ventana), contenedorV);

}
void VentanaIngreso::crearVentana() {
	/* creo ventana principal */
	ventana = NULL;
	this->ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	/* conecto la señal "delete_event" de la ventana a la callback
	 * on_delete_event() */
	//g_signal_connect(G_OBJECT(this->ventana), "delete_event", G_CALLBACK(
		//	on_delete_event), NULL);

	/* conecto la señal "destroy" de la ventana a la callback destruir()
	 * esta señal se emite cuando se llama a gtk_widget_destroy() */
	g_signal_connect(G_OBJECT(this->ventana), "destroy", G_CALLBACK(destruir),
			NULL);

	/* pongo un borde a la ventana (espacio libre al rededor del borde) */
	gtk_container_set_border_width(GTK_CONTAINER(this->ventana), 100);

}

void VentanaIngreso::crearTable() {

	table = NULL;
	/* create a table of 10 by 1 squares. */
	this->table = gtk_table_new(6, 1, FALSE);

//	gtk_box_pack_start(GTK_BOX(contenedorV), table, FALSE, FALSE, 10);

}
void VentanaIngreso::crearLabel() {
	label = NULL;
	this->label = gtk_label_new("Ingrese  su nombre de Usuario");

	gtk_table_attach((GtkTable*) this->table, this->label, 0, 1, 0, 1,
			GTK_SHRINK, GTK_SHRINK, 0, 0);

}

void VentanaIngreso::crearEntrada() {

	entrada = NULL;
	/* creo una entrada de texto */
	this->entrada = gtk_entry_new();

	gtk_table_attach((GtkTable*) this->table, this->entrada, 0, 1, 1, 2,
			GTK_SHRINK, GTK_SHRINK, 0, 0);

}
void VentanaIngreso::crearEntrada3() {
	entrada3 = NULL;
	/* creo una entrada de texto */
	this->entrada3 = gtk_entry_new();

	gtk_table_attach((GtkTable*) this->table, this->entrada3, 0, 1, 5, 6,
			GTK_SHRINK, GTK_SHRINK, 0, 0);

}
void VentanaIngreso::crearEntrada2() {

	entrada2 = NULL;
	/* creo una entrada de texto */
	this->entrada2 = gtk_entry_new();

	gtk_table_attach((GtkTable*) this->table, this->entrada2, 0, 1, 3, 4,
			GTK_SHRINK, GTK_SHRINK, 0, 0);

}

void VentanaIngreso::crearLabel2() {

	label2 = NULL;
	this->label2 = gtk_label_new("Ingrese el host o IP");

	gtk_table_attach((GtkTable*) this->table, this->label2, 0, 1, 2, 3,
			GTK_SHRINK, GTK_SHRINK, 0, 0);

}

void VentanaIngreso::crearLabel3() {
	label3 = NULL;
	this->label3 = gtk_label_new("Ingrese el puerto");

	gtk_table_attach((GtkTable*) this->table, this->label3, 0, 1, 4, 5,
			GTK_SHRINK, GTK_SHRINK, 0, 0);

}

void VentanaIngreso::crearBoton() {
	boton = NULL;
	/* creo un botón predefinido con un ícono de "Aceptar" */
	this->boton = gtk_button_new_from_stock("gtk-ok");

	/* conecto la señal "clicked" del botón a la callback on_boton_clicked()
	 * y le envío el widget entrada como dato adicional */
	g_signal_connect(G_OBJECT(this->boton), "clicked", G_CALLBACK(
			on_boton_clicked), this);

	gtk_table_attach((GtkTable*) this->table, this->boton, 0, 1, 6, 7,
			GTK_SHRINK, GTK_SHRINK, 0, 0);

}
void VentanaIngreso::crearBotonDeslog() {
	/* creo un botón predefinido con un ícono de "Aceptar" */
	botonDeslog = gtk_button_new_from_stock("desloguearme");
gtk_widget_set_sensitive(botonDeslog, false);
	/* conecto la señal "clicked" del botón a la callback on_boton_clicked()
	 * y le envío el widget entrada como dato adicional */
	g_signal_connect(
			G_OBJECT(this->botonDeslog),
			"clicked",
			G_CALLBACK(on_boton_clicked_logout), this);


	//gtk_box_pack_start(GTK_BOX(contenedorV), botonDeslog, false, FALSE, 10);
	std::cout<<"boton de deslog"<<std::endl;
}



void VentanaIngreso::crearLabel4() {
	label4 = NULL;
	this->label4 = gtk_label_new("El texto a editar:");

}

void VentanaIngreso::crearLabel5() {
	label5 = NULL;
	this->label5 = gtk_label_new("Mis amigos conectados:");

}
void VentanaIngreso::crearCamposTexto() {
	/* creo un contenedor que divide horizontalmente para poner mis widgets
	 * TRUE es para que todos los elementos sean de igual tamaño
	 * 10 es para que deje 10 píxels entre los elementos */
	contenedor = NULL;
	contenedor = gtk_hbox_new(TRUE, 10);

	gtk_box_pack_start(GTK_BOX(this->contenedor), label4, TRUE, TRUE, 10);

	gtk_box_pack_start(GTK_BOX(this->contenedor), label5, TRUE, TRUE, 10);
	gtk_box_pack_start(GTK_BOX(contenedorV), contenedor, false, FALSE, 10);

}

void VentanaIngreso::crearCamposTexto3() {
	/* creo un contenedor que divide horizontalmente para poner mis widgets
	 * TRUE es para que todos los elementos sean de igual tamaño
	 * 10 es para que deje 10 píxels entre los elementos */
	contenedor3 = NULL;
	contenedor3 = gtk_hbox_new(TRUE, 10);


	gtk_box_pack_start(GTK_BOX(contenedor3), table, FALSE, FALSE, 10);
	gtk_box_pack_start(GTK_BOX(contenedor3), botonDeslog, FALSE, FALSE, 10);

	gtk_box_pack_start(GTK_BOX(contenedorV), contenedor3, FALSE, FALSE, 10);



}

const char* utf8ToAscii(std::string str) {
	gchar* copia = new gchar[str.size() + 1];

	str.copy(copia, str.size(), 0);
	const gchar* asc = "ASCII";
	const gchar* utf = "UTF8";
	gchar fallBack[] = { '#' };

	gchar* strAscii = g_convert_with_fallback(copia, str.size(), utf, asc,
			fallBack, NULL, NULL, NULL);

	delete[] copia;
	return strAscii;
}

void hanAgregado(GtkWidget* texto, GtkTextIter* location, gchar * text, gint len,
		gpointer user_data) {

	int posicion = gtk_text_iter_get_offset(location);
	std::string asciiText = utf8ToAscii(text);
	std::cout << "el texto a agregar"<<asciiText<<"END" << std::endl;

	Cambio
			cambio(
					"A",
					((VentanaIngreso*) user_data)->getCliente()->getDocumentoConc()->getVersion(),0,
					posicion,  asciiText);
	std::cout << "el cambio enviado"<<cambio.getStdCambio()<< std::endl;


	((VentanaIngreso*) user_data)->getCliente()->EnviarCambio(cambio);
}


void hanBorrado(GtkTextBuffer *textbuffer,    GtkTextIter   *start,
        GtkTextIter   *end,
        gpointer       user_data) {
std::cout << "en han borrado"<< std::endl;



	int inicio = gtk_text_iter_get_offset(start);
	gchar* texto = gtk_text_buffer_get_slice    (textbuffer, start, end, true);

	std::string asciiText = utf8ToAscii(texto);
	Cambio
			cambio(
					"B",
					((VentanaIngreso*) user_data)->getCliente()->getDocumentoConc()->getVersion(),0,
					inicio, asciiText);
	((VentanaIngreso*) user_data)->getCliente()->EnviarCambio(cambio);
	std::cout << "el cambio enviado"<<cambio.getStdCambio()<< std::endl;

}

void VentanaIngreso::crearTexto() {
	this->docTagTable = NULL;
	this->docTagTable = gtk_text_tag_table_new();
	this->texto = NULL;
	this->texto = gtk_text_buffer_new(this->docTagTable);

	this->view = NULL;
	this->view = gtk_text_view_new_with_buffer(this->texto);

	gtk_text_view_set_editable(GTK_TEXT_VIEW(this->view), true);
	gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(this->view), true);

	gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(this->view), GTK_WRAP_WORD_CHAR);
	gtk_text_view_set_left_margin(GTK_TEXT_VIEW(this->view), 5);
	gtk_text_view_set_right_margin(GTK_TEXT_VIEW(this->view), 5);

	this->swindow = gtk_scrolled_window_new(NULL, NULL);

	// gtk_widget_set_size_request(swindow, 400, 300);

	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(this->swindow),
			GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_container_add(GTK_CONTAINER(this->swindow), this->view);

	gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(this->swindow),
			GTK_SHADOW_IN);

	std::cout << "aantes" << std::endl;

	insertSignal = g_signal_connect(G_OBJECT(texto), "insert_text",GTK_SIGNAL_FUNC(hanAgregado),(gpointer) this);
	deleteSignal = g_signal_connect(G_OBJECT(texto), "delete_range",GTK_SIGNAL_FUNC(hanBorrado),(gpointer) this);
	std::cout << "luego" << std::endl;

}

Cliente* VentanaIngreso::getCliente() {
	return this->cliente;
}

GtkWidget* VentanaIngreso::getView() {
	return this->view;
}

void VentanaIngreso::crearLista() {

	docTagTable2 = gtk_text_tag_table_new();
	lista = gtk_text_buffer_new(docTagTable);
	view2 = gtk_text_view_new_with_buffer(lista);

	gtk_text_view_set_editable(GTK_TEXT_VIEW(view2), false);
	gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(view2), false);
	gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(view2), GTK_WRAP_WORD_CHAR);
	gtk_text_view_set_left_margin(GTK_TEXT_VIEW(view2), 5);
	gtk_text_view_set_right_margin(GTK_TEXT_VIEW(view2), 5);

	swindow2 = gtk_scrolled_window_new(NULL, NULL);

	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(swindow2),
			GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_container_add(GTK_CONTAINER(swindow2), view2);
	gtk_text_view_set_editable(GTK_TEXT_VIEW(view2), false);
	gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(view2), false);

	gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(swindow2),
			GTK_SHADOW_IN);

	gtk_text_buffer_set_text(
			lista,
			"Aquí aparecerán tus amigos que editan el texto simultáneamente a tí.",
			-1);

}
void VentanaIngreso::crearCamposTexto2() {
	/* creo un contenedor que divide horizontalmente para poner mis widgets
	 * TRUE es para que todos los elementos sean de igual tamaño
	 * 10 es para que deje 10 píxels entre los elementos */
	contenedor2 = gtk_hbox_new(TRUE, 10);

	gtk_box_pack_start(GTK_BOX(contenedor2), swindow, true, true, 0);
	gtk_box_pack_start(GTK_BOX(contenedor2), swindow2, true, true, 0);

	gtk_box_pack_start(GTK_BOX(contenedorV), contenedor2, TRUE, TRUE, 10);

}

void VentanaIngreso::mostrar() {
	gtk_widget_show_all(this->ventana);
	gtk_main();
}

//TODO: Borrar una vez terminado el debugging
VentanaIngreso::~VentanaIngreso() {
this->cliente->Desloguearse();
this->cliente->join();
delete cliente;
	std::cout << "////Destructor VentanaIngreso/////" << std::endl;
}

VentanaIngreso::VentanaIngreso(const VentanaIngreso& ventanaIngreso){
	std::cout << "////CONST COPIA VentanaIngreso/////" << std::endl;
}
