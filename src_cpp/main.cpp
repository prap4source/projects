#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "hash.hpp"
using namespace std;

/* fptr is function pointer which takes void and returns void */
typedef void (*fptr)(int argc, char *argv[]);
typedef struct scase {
	const char *str;
	fptr func;
}stringcase;
/* Dictonary of string to function pointers */
stringcase myCases[] = {{"hash", start_hash},
		        {"string", start_stests}};

int main(int argc, char *argv[]) {
	bool not_found = true;
	int size_cases = (sizeof(myCases)/ sizeof(myCases[0]));
	if (argc >= 2) {
	   for (stringcase *pcases = myCases; 
		pcases != myCases +  size_cases ; pcases++) {
		if ((strcmp(argv[1], pcases->str) == 0)) {
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
	return 0;
}
