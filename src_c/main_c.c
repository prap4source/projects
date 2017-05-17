/* Main program to call socket server /client or hash programs */
#include <stdio.h>
#include "common.h"
/* fptr is function pointer which takes void and returns void */
typedef void (*fptr)(void);
typedef struct scase {
	char *str;
	fptr func;
}stringcase;
/* Dictonary of string to function pointers */
stringcase myCases[] = {{"server", start_server},
		      {"client", start_client}, 
		      {"hash", start_hprogram},
		      {"md5csum",start_md5}};

int main(int argc, char *argv[]) {
	
	if (argc >= 2) {
	   for (stringcase *pcases = myCases; 
		pcases != myCases + (sizeof(myCases)/ sizeof(myCases[0])) ; pcases++) {
			
		if ((strcmp(argv[1], pcases->str) == 0)) 
			(*pcases->func)();
	    }
	}
	return 0;
}
