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

/* Following program expects to return time and signum, 
 * but due to error is not printing, fix it  */
#define signum(x) ((x > 0) ? (x >0) : (-1)) 
int signum_main()
{
    const int end = 3;
    const int start = -2;
    int idx = start;
 
    while (idx != end)
    {
	#ifdef  ORGINAL_ERROR
		printf("%+d => %+d\n", idx, signum(idx++));
	#else /* -Added this to fix it .*/
		idx++; 
		printf("%+d => %+d\n", idx, signum(idx));
	#endif
    }
 
    return 0;
}
