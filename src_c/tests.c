/*
 * tests.c Some coding challenges asked in interviews
 * Copyright 2017 Pradeep Gopanapalli 
 * 
 */

#include "common.h"
#include "bitsops.h"
#include <stdlib.h>

/* (TBD)(INT_QUEST)https://www.careercup.com/question?id=14424684 */
char *read4k(char *buf, int num) {
	return NULL;
}

void printwithput(int val) {
	int rem;
	if (val) {
		rem = val %10;
		printwithput(val/10);
		putc(rem + '0', stdout);
	} 
}

void start_test(int argc, char *argv[]) {
	log ("num of arguments %d",argc);
	
	if (argc <= 3) {
		log_err("Usage: <tests> <arg>");
		return ;
	}
	
	if ((strcmp(argv[2],"multiply") == 0) && (argc >= 5)) {
			char *result = multiplyStrings(argv[3], argv[4]);
			log ("(%s:%s)", argv[2], argv[3]);
			if (result) {
				printf("mulitply(%s:%s) is %s \n", argv[3], argv[4], result);
				free(result);
			}
	} else if ((strcmp(argv[2],"add") == 0) && (argc >= 5)) {
			char *result = addStrings(argv[3], argv[4]);
			log ("Test (%s:%s)", argv[3], argv[4]);
			if (result) {
				printf("addString of (%s:%s) is %s \n", argv[3], argv[4], result);
				free(result);
			}
	} else if ((strcmp(argv[2],"finddiff") == 0) && (argc >= 5)) {
			char result = findDifferene(argv[3], argv[4]);
			log ("Test (%s:%s)", argv[3], argv[4]);
			if (result) {
				printf("difference of (%s:%s) is %c \n", argv[3], argv[4], result);
			}
	} else if (strcmp(argv[2], "compvers") == 0) {
			int result = compareVersion(argv[3], argv[4]);
			printf("compare(%s:%s) result%d\n", argv[3], argv[4], result);
	} else if (strcmp(argv[2], "atoi") == 0) {
		       int result = myAtoi(argv[3]);
		       printf ("atoi(%s) == %d \n", argv[3], result);
	} else if (strcmp(argv[2], "array") == 0) {
			int a[] = {1, 0, -1, 2, 1, 3, -2, -3, 0};
			int m = sizeof(a)/sizeof(a[0]);
			printDuplicates(a, m);
			printf("findMinSlideSize(%d) \n", findMinSlideSize(a, m, 3 ));
	} else if (strcmp(argv[2], "putc") == 0) {
		printf("print element %s in putc \n",argv[3]);
		printwithput(myAtoi(argv[3])); 
	} else if (strcmp(argv[2], "theatre") == 0) {
		int a[] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
		int m = sizeof(a)/sizeof(a[0]);
		printf("Number of people to fill %d\n",findSlots(a, m));
	} else if (strcmp(argv[2], "generic") == 0) {
		for (int i =1; i<=4;i++) {
			/* In a system with 4 GB RAM we can allocate upto 2^32 virtual memory
			 * in 8 GB upto 2^33 and so on */			
			uint64_t alloc_mem = pow(2,32);
			uint64_t *addr =  malloc(alloc_mem);
			printf("(%p:%lld) mem alloc\n", addr, alloc_mem);
			set_bit(35, (ulong *)addr);
			free(addr);
		}
	} else {
		log_err("Usage: <tests> <>");
	}
}

