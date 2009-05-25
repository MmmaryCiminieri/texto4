#include <gtk/gtk.h>
#include "client_Vista.h"
#include "client_Cliente.h"
#include <iostream>

int escucharCambios(void* cliente) {

	//no se ejecuta mas
	return true;
}

/* Programa */
int main(int argc, char* argv[]) {

	//Cliente cliente;

	/* procesa línea de comandos e inicializa */
	gtk_init(&argc, &argv);

	Vista vista/*(&cliente)*/;

	/*se llama cada 500 mseg tiempo a la funcion dada*/
	//guint32 intervalo = 500;
	//g_timeout_add (intervalo, escucharCambios,(void*) &cliente);
	vista.mostrar();

	//aca manejo la vista y envio cambios
	std::cout << "---------------MAIN-----------------" << std::endl;

	return 0;
}
