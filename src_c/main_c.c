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
			{"server_hash", start_server},
		      {"client", start_client}, 
		      {"hash", start_hprogram},
		      {"md5csum",start_md5}};

int main(int argc, char *argv[]) {
	bool not_found = true, hash = false;
	int size_cases = (sizeof(myCases)/ sizeof(myCases[0]));
	if (argc >= 2) {
	   for (stringcase *pcases = myCases; 
		pcases != myCases +  size_cases ; pcases++) {
		if ((strcmp(argv[1], pcases->str) == 0)) {
			not_found = false;
			if ((strcmp(argv[1], "server_hash") == 0)) {
				log("create hash %s len%d", argv[1], size_cases);
				hash = true;
				hash_init(MAX_HASH);
			}
			(*pcases->func)();
		}
	    }
	}
	if (not_found) {
		printf("Usage: %s <",argv[0]);
		for (int i = 0; i < size_cases; i++)
			printf("%s/", myCases[i].str);
		printf(">\n");
	}
	if (hash)
		hash_fini();
	return 0;
}
