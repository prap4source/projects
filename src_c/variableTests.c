/*
 * Copyright 2017 Pradeep Gopanapalli
 * variableTests.c
 * Some coding challenges asked in interviews
 */
#include "common.h"
#include "operations.h"

/* reverse a integer x and return reversed value */
int reverseInt(int x) {
    int y = 0;
    while (x) {
        int temp = y;
        y = (x %10) + y *10;
        x = x /10;
        if (y/10 != temp) { /* Check for underflow or overflow */
        	printf("underflow/overflow returning zero(%d:%d) \n",temp, y/10);    
                return 0;
        }
    }
    return y;
}

/* Find fibannoci series using Memorization method ,Dynammic programming method 1 
 Memoization (Top Down): The memoized program for a problem is similar to the recursive 
 version with a small modification that it looks into a lookup table before computing 
 solutions. We initialize a lookup array with all initial values as NIL. Whenever we 
 need the solution to a subproblem, we first look into the lookup table. If the 
 precomputed value is there then we return that value, otherwise, 
 we calculate the value and put the result in the lookup table so that it can be reused later.*/
#define MAX 255
int f[MAX];
int fibN(int n) {
    if (f[n] == -1) {
        if (n <= 1)
           f[n] = n;
        else
            f[n] = fibN(n-1) + fibN(n-2);
    }
    
    return f[n];
}
int findfibN(int n) {
    int val;
    if (n >= MAX) {
        printf("n:%d >= MAX:%d\n", n, MAX);
        return 1;
    }
	for (int i =0;i<=n;i++)
	    f[i] = -1;
	val = fibN(n);
	printf("n:%d fib:%d \n", n, val);
	return 0;
}
	
/* Find fibannoci series using tabulation method ,Dynammic programming method 2
(Bottom Up): The tabulated program for a given problem builds a table in bottom up fashion and 
returns the last entry from table. For example, for the same Fibonacci number, we first calculate 
fib(0) then fib(1) then fib(2) then fib(3) and so on. So literally, we are building the solutions of subproblems bottom-up. */
int findFibN(int n) {
	int f[n+1];
	f[0] = 0;
	f[1] =1;
	for (int i =2;i<=n;i++)
	    f[i] = f[i-1] + f[i-2];
	return f[n+1];
}

/* Print val without using print and using put */
int printwithput(int val) {
	int rem;
	static int first = 0;
	if (val) {
		rem = val %10;
		first++;
		printwithput(val/10);
		putc(rem + '0', stdout);
		first--;
		if (first == 0)
			printf("\n");

	} 
	return 0;
}

/* Wrappers for testType -> function */
typedef int (*fptr1) (int val);
typedef int (*fptr2) (int val1, int val2);
typedef struct testToRun {
	/* Type of test*/
	char *testType;
	/* Number of parameters */
	int params;
	fptr1 func1;
	fptr2 func2;
	char *descr;
}testRun;

/* testRun tests[] will be used for invoking corresponding tests */
static testRun tests[] = {{"putPrint", 1, printwithput, NULL, "Print n using put"},
		          {"reverseInt", 1, reverseInt, NULL, "reverse Integer"}
			 };

/* Usage function */
static inline void usage(int argc, char *argv[]) {
	testRun *ptr;
	int size = (sizeof(tests) / sizeof(tests[0]));
	for (ptr = tests; ptr != tests + size; ptr++)
		log_err("usage(): %s %s %s <%d arguments> ,description:%s",
			  argv[0], argv[1], ptr->testType, ptr->params, ptr->descr);
}

/* Starting point of Array tests*/
void start_variabletest(int argc, char *argv[]) {
	log ("num of arguments %d",argc);
	
	if (argc <= 3) {
		usage(argc, argv);
		return ;
	} 

	bool not_found = true;
	testRun *ptr;
	int tests_size = sizeof(tests) / sizeof(tests[0]) ;
	for (ptr = tests; ptr != tests + tests_size; ptr++) {
		int params = argc - ptr->params;
		if (strcmp(argv[2], ptr->testType) == 0) {
			/* If it has two parameters */
			if ((argc - ptr->params - 3) != 0)
			    break;
			not_found = false;
			if (ptr->params == 1) {
				int val = myAtoi(argv[3]);
				printf("value:%d %s==> value:%d \n",val, ptr->testType, (*ptr->func1)(val));
			} else {
				(*ptr->func2)(myAtoi(argv[3]), myAtoi(argv[4]));
			}
		}

	}

	if (not_found) {
		usage(argc, argv);
		return;
	}
}
