#include <gtk/gtk.h>
#include "client_Vista.h"
#include <iostream>



/* Programa */
int main(int argc, char* argv[]) {


	/* procesa línea de comandos e inicializa */
	gtk_init(&argc, &argv);

	Vista vista;

	/*se muestra la interfaz gráfica desde donde toodo sucede*/
	vista.mostrar();


	std::cout << "---------------MAIN-----------------" << std::endl;

	return 0;
}
