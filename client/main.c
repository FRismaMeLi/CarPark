#include "app.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define debug 0

int main (int argc, char *const argv[]) {

	puts("\t\t ..:: Trabajo Final - Computacion II - CarPark Client ::..");

	int socketDescriptor = 0;

	// Manejo de opciones
	configuration *conf = (configuration *)malloc(sizeof(configuration));
	optionsHandler(argc, argv, conf);

	// Configuro el cliente desde archivo
	clientConf *servParams = (clientConf *)malloc(sizeof(configuration));
	if ( 0 > configServer("servidor.cfg",servParams->serverIp,servParams->port) ) {
		free(conf);
		free(servParams);
		return -1;
	}
	// Abro conexion con el socket
	//establishConnection(&socketDescriptor,servParams);

	// Hago el trabajo
	switch (conf->opt) {
		case 'c':
			if (debug) puts("Crear");
			createTicket(socketDescriptor);
			break;
		case 'd':
			if (debug) puts("Eliminar");
			deleteTicket(socketDescriptor,conf->slotId);
			break;
		case 's':
			if (debug) puts("Status");
			statusTicket(socketDescriptor,conf->slotId);
			break;
	}
	//char buff[15];
	//read(socketDescriptor,buff,15);
	//printf("El server escribio: %s\n",buff);

	// Muero
	free(conf);
	free(servParams);
	puts("Adios");

	return 0;
}