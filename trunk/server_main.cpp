#include <glib.h>
#include <glib/gprintf.h>
#include <gtk/gtk.h>

#include "common_MSocket.h"
#include  "server_Cliente.h"
#include  "server_ServidorEx.h"
#define PUERTO 8080
#define LOCAL_HOST 1270000
#define MAXCANTUS 27

/* Programa */
int main(int argc, char* argv[]){

	unsigned short puerto = 8080;
	int cantClientes = 25;
	Servidor servidor(puerto, cantClientes);
	ServidorEx servidorExecutable(&servidor);
	std::cout<< "en el main "<<std::endl;

	servidor.cerrarServidor();
    return 0;
}
