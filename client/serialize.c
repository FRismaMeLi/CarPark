#include "app.h"

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

char * const kPattern = "#:%li|a:%d|c:%s|f:%d|o:%lu";

#define debug 0

int serialize(slot s, char *serialized) {

	int d_id 		= floor(log10(abs(s.id))) + 1;
	int d_available = floor(log10(abs(s.available))) + 1;
	int d_floor 	= floor(log10(abs(s.floor))) + 1;
	int d_offset 	= floor(log10(abs(s.offset))) + 1;
	if ( 0 > snprintf(serialized, d_id + d_available + strnlen(s.idCli,sizeof(s.idCli)) + d_floor + d_offset + 15 ,kPattern, s.id, s.available, s.idCli, s.floor, s.offset) ) {
		write(STDERR_FILENO,"serialize snprintf",18);
		return -1;
	}

	if (debug) printf("Serialize Resultado %s\n",serialized);
	return 0;
}
