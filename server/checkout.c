#include "app.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define debug 1

int checkout(struct slot *start, struct slot *result, pthread_mutex_t *mutex) {

	struct slot *node = start;
	if ( 0 != pthread_mutex_lock(mutex) ) {
		perror("pther_mutex_lock");
		return -1;
	}
	int slotId = result->id;
	do {
		if ( slotId == node->id && node->available == false) {
			time_t *rawtime = (time_t *)malloc(sizeof(time_t));
			time(rawtime);
			// Maping to result
			result->id 				=	node->id;
			result->available 		= 	false;
			result->floor 			= 	node->floor;
			result->offset 			= 	node->offset;
			result->checkInTime 	= 	node->checkInTime;
			printf("La hora de entrada fue %s\n",asctime(result->checkInTime));
			localtime_r(rawtime,result->checkOutTime);
			strncpy(result->idCli,node->idCli,10);
			strncpy(result->bill,node->bill,16);
			printf("La hora de salida fue %s\n",asctime(result->checkOutTime));
			
			// Make the node available again
			node->available 		= 	true;
			node->checkInTime		= 	NULL;
			node->checkOutTime		= 	NULL;
			memset(node->bill,'\0',16*sizeof(char));
			memset(node->idCli,'\0',10*sizeof(char));
			if (debug) { puts("Checkout:"); printLocation(result);}
			break;
		} else {
			node = node->next;
			result->id = -1;
		}
	}while(node != NULL);
	if ( 0 != pthread_mutex_unlock(mutex) ) {
		//no se puede liberar el mutex
		perror("pthread_mutex_unlock");
		return -1;
	}
	return 0;
}	
