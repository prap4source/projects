#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "common.hpp"
using namespace std;

int main(int argc, char *argv[]) {
	bool not_found = true;
	int size_cases = (sizeof(myCases)/ sizeof(myCases[0]));
	if (argc >= 2) {
	   for (stringcase *pcases = myCases; 
		pcases != myCases +  size_cases ; pcases++) {
		if (!strcmp(argv[1],"all") || (strcmp(argv[1], pcases->str) == 0)) {
			not_found = false;
			printf("\n starting %s \n", pcases->str);
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
