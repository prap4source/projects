/*
 * main_c.c Main program to call socket server /client or hash programs
 * Copyright 2017 Pradeep Gopanapalli 
 * 
 */
#include <stdio.h>
#include "common.h"
long long int alloc_mem;
long long int freed_mem;
/* fptr is function pointer which takes void and returns void */
typedef void (*fptr)(int argc, char *argv[]);
typedef struct scase {
	char *str;
	fptr func;
}stringcase;
/* Dictonary of string to function pointers */
stringcase myCases[] = {{"server", start_server},
		      {"client", start_client}, 
		      {"hash", start_hprogram},
		      {"md5csum",start_md5},
		      {"tests",start_test},
		      {"strings",start_stringtest},
		      {"arrays",start_arraytest},
		      {"variables",start_variabletest},
		      {"bittests",start_bittests},
		      {"singlelist",start_llist},
		      {"cbasic", start_cbatests},
			  {"threads", start_thrtests}};

int main(int argc, char *argv[]) {
	bool not_found = true;
	int size_cases = (sizeof(myCases)/ sizeof(myCases[0]));
	if (argc >= 2) {
	   for (stringcase *pcases = myCases; 
		pcases != myCases +  size_cases ; pcases++) {
		if (!strcmp(argv[1], pcases->str)) {
			not_found = false;
			(*pcases->func)(argc, argv);
		}
	    }
	}
	if (not_found) {
		printf("Usage: %s <",argv[0]);
		for (int i = 0; i < size_cases; i++)
			printf("%s/", myCases[i].str);
		printf(">\n");
	}
	log_info("memory (%lld:%lld)", alloc_mem, freed_mem);
	return 0;
}
