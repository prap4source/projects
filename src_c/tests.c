/*
 * tests.c Some coding challenges asked in interviews
 * Copyright 2017 Pradeep Gopanapalli 
 * 
 */

#include "common.h"
#include "bitsops.h"
#include <stdlib.h>


void generic() {
	for (int i =1; i<=4;i++) {
		/* In a system with 4 GB RAM we can allocate upto 2^32 virtual memory
		 * in 8 GB upto 2^33 and so on */			
		uint64_t alloc_mem = pow(2,32);
		uint64_t *addr =  malloc(alloc_mem);
		printf("(%p:%lld) mem alloc\n", addr, alloc_mem);
		set_bit(35, (ulong *)addr);
		free(addr);
	}
}

void start_test(int argc, char *argv[]) {
	log ("num of arguments %d",argc);
	
	if (argc <= 3) {
		log_err("Usage: <tests> <arg>");
		return ;
	}
	
	if (strcmp(argv[2], "generic") == 0) {
		generic();
	} else {
		log_err("Usage: <tests> <>");
	}
}

