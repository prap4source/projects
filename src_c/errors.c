/*
 * Copyright 2017,2018,2019 Pradeep Gopanapalli
 * errors.c
 * Finding errors and what happens in code challenges
 */
#include "common.h"
#include "operations.h"

/* Static pointer usage  
 * In following code snippets if f2 is called twice the second time 
 * it goes to else condition and *ptr will be pointing to
 * previous “a “address which is already gone during stack unwinding , 
 * so the program will result in some corruption in side stack of the program
 */
void f2(int *a) {
	static int *ptr;
	if (ptr == NULL)
		ptr = a;
	else 
		*ptr = 10;
}
void f1() {
	int a = 10;
	f2(&a);
}

