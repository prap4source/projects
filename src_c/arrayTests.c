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

/* Target of partitions is, given an array and an element x of array as pivot, 
   put x at its correct position in sorted array and put all smaller elements 
   (smaller than x) before x, and put all greater elements (greater than x) after x. 
   All this should be done in linear time. */
int partition(int arr[], int low, int high) {
	int pivot, i, j;
	pivot = arr[high];
	i = (low-1); /* Index of smaller element*/
	for (j = low; j < high; j++) {
		if (a[j] <= pivot) { /* if current element is smaller then pivot*/
			i++; /* Increment index of smaller element /
			if (i != j) /* optimizimation */
			  swap(a[i], a[j]);
		}
	}
	if (i != (high-1)) /* optimizimation */
	    swap(a[i+1], a[high]);
	return (i+1);
}
/* Quick sort time complexity o(nlogn) and Doesnt require any extra space
   https://www.geeksforgeeks.org/quick-sort/ 
    QuickSort is a Divide and Conquer algorithm. It picks an element as pivot and partitions the given array around the picked pivot. There are many different versions of quickSort that pick pivot in different ways.
    Always pick first element as pivot.
    Always pick last element as pivot (implemented below)
    Pick a random element as pivot.
    Pick median as pivot.
*/
void quicksort(int arr[], int low, int high) {
	int pi; /* partition */
	if (low < high) {
		pi = partition(arr, low, high);
		quicksort(arr, low, pi-1); /*before pivot */
		quicksort(arr, pi+1, high); /*after pivot */
	}
}
	
/* selection sort works by iterating array and finding a minimum element 
   and putting it to start of list  The algorithm maintains two subarrays in a given array.
1) The subarray which is already sorted.
2) Remaining subarray which is unsorted.
In every iteration of selection sort, the minimum element (considering ascending order) from the unsorted subarray is picked and moved to the sorted subarray. 
o(n^2) space o(1)
https://www.geeksforgeeks.org/selection-sort/
*/
void selectionsort(int arr[], int size) {
	int i, j;
	for (i=0; i<size-1; i++) {
		int min_idx = i;
		for (j=1; j < size ;j++) {
			if (a[j] < a[min_idx]) 
				min_idx = j;
		}
		swap(a[i], a[min_idx]);
	}
}
			
}
