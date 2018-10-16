/*
 * Copyright 2017 Pradeep Gopanapalli
 * arrayTests.c
 * Some coding challenges asked in interviews
 */
#include "common.h"
#include "operations.h"

int findMaxinArray(int *arr, int len) {
	int max_no = arr[0], i;
	for (i=1; i < len ;i++) {
		max_no = max(max_no, arr[i]);
	}
	return (max_no);
}
/** Find duplicates in a array using bitmask INT_QUEST
 *Use bitmask where each bit represents number 
 *TBD:Optimize this to decrease size of bitmask
 **/
void printDuplicates(int *arr, int len) {
	int i;
	int max = findMaxinArray(arr, len);
	int alloc = ((max/8)*sizeof(char)) + 1;
	int *bitmask = malloc(alloc);
	*bitmask =0;
	log ("max(%d) len(%d) alloc(%d)", max, len, alloc);
	for (i=0;i<len; i++) {
		if (*(bitmask) & (1<<arr[i]))
			printf("%d repeated \n", arr[i]);
		else 
		    *(bitmask) |= (1<<arr[i]);
	}
	free(bitmask);
}


/**  Find minimum sliding window size (INT_QUEST)
 * e.g. array[7] ={ 1, 0, -1, 2, 1, 0, -2 } ,swSize = 3
 * Windows ===> { 1, 0, -1 } = 0 { 0, -1, 2} = 1 { -1, 2, 1} = 2 { 2, 1, 0} = 3 {1, 0, -2} = -1
 * m >= swSize*2
 */
int findMinSlideSize(int arr[], int m, int swSize) {
      int min_size=INT_MAX;
      int curr_size = 0, i;
      for (i = 0; i < swSize;i++) 
	    curr_size += arr[i];
      min_size = min(min_size, curr_size);
      for (i = swSize;i < m; i++) {
              curr_size -= arr[i-swSize];
	      curr_size += arr[i];
	      min_size = min(curr_size, min_size);
     }
     
     return (min_size);
}

/* Find fibannoci series using Memorization method ,Dynammic programming method 1 
 Memoization (Top Down): The memoized program for a problem is similar to the recursive 
 version with a small modification that it looks into a lookup table before computing 
 solutions. We initialize a lookup array with all initial values as NIL. Whenever we 
 need the solution to a subproblem, we first look into the lookup table. If the 
 precomputed value is there then we return that value, otherwise, 
 we calculate the value and put the result in the lookup table so that it can be reused later.*/
int f[MAX] = -1;
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
}
