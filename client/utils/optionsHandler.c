#include "optionsHandler.h"

#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define debug 0

void optionsHandler (int argc, char* const argv[], configuration *conf) {

	//Chequear si fue iniciado con algun argumento, sino, salir
	if (1 == argc) {
		write(STDERR_FILENO,"No enough args\n",15);
		exit(EXIT_FAILURE);
	}

	int opt = 0;
    // Argument handling
    opterr=1;   // Disables getopt() error printing.
	while ((opt = getopt(argc, argv, "cd:s:h")) >= 0 ){ // -c create -d delete -s status -h help
		switch (opt){
			case 'c':
				if (debug) printf("Create a ticket\n");
				conf->opt = 'c';
				break;
			case 'd':
				if (debug) printf("Delete ticket\n");
				conf->opt = 'd';
				if (strlen(optarg) == SLOT_ID_LENGTH) {
					strncpy(conf->slotId, optarg, strnlen(optarg,SLOT_ID_LENGTH)+1);
					if (debug) printf("Ticket:%s\n",optarg);
				} else {
					printf("Ticket lenght should be of %d chars\n",SLOT_ID_LENGTH);
					exit(EXIT_FAILURE);
				}
				break;
			case 's':
				if (debug) printf("Status\n");
				conf->opt = 's';
				if (strlen(optarg) == SLOT_ID_LENGTH) {
					strncpy(conf->slotId, optarg, strnlen(optarg,SLOT_ID_LENGTH)+1);
					if (debug) printf("Ticket:%s\n",optarg);
				} else {
					printf("Ticket lenght should be of %d chars\n",SLOT_ID_LENGTH);
					exit(EXIT_FAILURE);
				}
				break;
			case 'h':
			case '?':
				puts("-c ask for a creation of a new ticket\n-d {ticketId} ask for a ticket number to be finished\n-s {ticketId} status of a ticket\n-h help");
                exit(EXIT_SUCCESS);
			default:
				puts("Sintaxis ambigua. Intente ejecutar con -h para mas detalles");
                exit(EXIT_SUCCESS);
		}
	}
}
