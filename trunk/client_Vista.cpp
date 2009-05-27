/*
 * Vista.cpp
 *
 *  Created on: Apr 25, 2009
 *      Author: mmmary
 */
#include <stdio.h>
#include <iostream>
#include <string.h>
#include "client_Vista.h"

Vista::Vista() {

	this->ventana.setVista(this);
	std::cout << "////CREO VISTA/////" << std::endl;
	return;
}

void Vista::ErrorConectar() {
	//TODO BORRAR AL CLIENTE POR Q ES COMO Q YA ESTA INGRESADO.... NO?
	GtkWidget* ventanaerror = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL,
			GTK_MESSAGE_WARNING, GTK_BUTTONS_OK,
			"No se ha podido realizar la conexión con el servidor. \n Espere un momento y vuélvalo a intentar.");
	gtk_window_set_title(GTK_WINDOW(ventanaerror), "Error");
	gtk_dialog_run( GTK_DIALOG(ventanaerror));
	gtk_widget_destroy(ventanaerror);
	this->ventana.bloquearBotonDeslog();
}

void Vista::mostrar() {
	ventana.mostrar();
}
VentanaIngreso* Vista::getVentana() {
	return &ventana;
}
void Vista::agregarAmigo(const char* nombre) {

	GtkTextIter it;
	gtk_text_buffer_get_end_iter(this->ventana.getLista(), &it);
	gtk_text_buffer_insert(this->ventana.getLista(), &it, nombre,
			strlen(nombre));

}
void Vista::refrescarLista() {
	/*Refresco la vista*/
	std::list<std::string> lista = this->ventana.getCliente()->getAmigos();
	 std::list<std::string>::iterator it;
	std::string nombreCliente;
	gtk_text_buffer_set_text( this->ventana.getLista(),"",-1);
		 for( it = lista.begin(); it != lista.end(); ++it ) {
		       nombreCliente = *it;
		       this->agregarAmigo(nombreCliente.c_str());
		       }
}
void Vista::cargarDocumento(std::string contenido) {

	g_signal_handler_block(this->ventana.getTexto(),
			this->ventana.getinsertSignal());
	gtk_text_buffer_set_text(this->ventana.getTexto(), contenido.c_str(), -1);
	g_signal_handler_unblock(this->ventana.getTexto(),
			this->ventana.getinsertSignal());

}

void Vista::agregar(const char* str, int posicion) {

	g_signal_handler_block(this->ventana.getTexto(),
			this->ventana.getinsertSignal());

	GtkTextIter start, end;
	gtk_text_buffer_get_start_iter(this->ventana.getTexto(), &start);
	gtk_text_buffer_get_end_iter(this->ventana.getTexto(), &end);
	gchar* texto = gtk_text_iter_get_slice(&start, &end);

	int longitud = strlen(texto);

	if (posicion < longitud) {
		GtkTextIter it;
		gtk_text_buffer_get_iter_at_offset(this->ventana.getTexto(), &it,
				posicion);
		gtk_text_buffer_insert(this->ventana.getTexto(), &it, str, -1);

	} else if (posicion == longitud) {
		gtk_text_buffer_get_end_iter(this->ventana.getTexto(), &end);
		gtk_text_buffer_insert(this->ventana.getTexto(), &end, str, -1);

	} else {

		int pad = posicion - longitud;
		for (int j = 0; j <= (pad - 1); j++) {
			/*  inserto un espacio  */
			std::string espacio = " ";
			gtk_text_buffer_get_end_iter(this->ventana.getTexto(), &end);
			gtk_text_buffer_insert(this->ventana.getTexto(), &end,
					espacio.c_str(), -1);
		}
		GtkTextIter it;
		gtk_text_buffer_get_iter_at_offset(this->ventana.getTexto(), &it,
				posicion);
		gtk_text_buffer_insert(this->ventana.getTexto(), &it, str, -1);

	}

	g_signal_handler_unblock(this->ventana.getTexto(),
			this->ventana.getinsertSignal());

}

void Vista::borrar(const char* str, int posicion) {
	GtkTextIter it;
	GtkTextIter it2;
	gtk_text_buffer_get_iter_at_offset(this->ventana.getTexto(), &it, posicion);
	gtk_text_buffer_get_iter_at_offset(this->ventana.getTexto(), &it2, (strlen(
			str) + posicion));
	g_signal_handler_block(this->ventana.getTexto(),this->ventana.getdeleteSignal());

	gtk_text_buffer_delete(this->ventana.getTexto(), &it, &it2);
	g_signal_handler_unblock(this->ventana.getTexto(),this->ventana.getdeleteSignal());

}


Vista::~Vista() {
	std::cout << "////BORRO VISTA/////" << std::endl;
}
