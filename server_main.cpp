
#include <iostream>
#include "common_MSocket.h"
#include  "server_Cliente.h"
#include  "server_ServidorEx.h"

#define PUERTO 8080
#define LOCAL_HOST 1270000
#define MAXCANTUS 27

/* Programa */
int main(int argc, char* argv[]){

	unsigned short puerto = PUERTO; //=servidor.setPuerto();

	/*servidor que maneja la logica  de la modificacion del texto*/
	Servidor servidor(puerto, MAXCANTUS);

	/*servidor que escucha a nuevos clientes*/
	ServidorEx servidorExecutable(&servidor);
	if(servidorExecutable.getIsValido()){
	/*creo un  nuevo hilo para aceptar clientes*/
			servidorExecutable.execute();
	}else{
		std::cout<<"Hubo un error en la conexion. Vuelva a intentarlo en otro momento."<<std::endl;
	}
	std::cout<< "en el main "<<std::endl;

	servidor.cerrarServidor();
    return 0;
}
