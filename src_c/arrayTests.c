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

/* Target of partitions is, given an array and an element x of array as pivot, 
   put x at its correct position in sorted array and put all smaller elements 
   (smaller than x) before x, and put all greater elements (greater than x) after x. 
   All this should be done in linear time. */
int partition(int arr[], int low, int high) {
	int pivot, small, j;
	pivot = arr[high]; /* select high as pivot, there are other ways to do this */
	small = (low-1); /* Index of smaller element*/
	for (j = low; j < high; j++) {
		if (arr[j] <= pivot) { /* if current element is smaller then pivot*/
			++small; /* Increment index of smaller element */
			if (small != j) /* optimizimation */
			  swap(arr[small], arr[j]);
		}
	}
	++small;
	if (small != (high)) /* optimizimation */
	    swap(arr[small], arr[high]);

	return (small);
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
void selectionsort(int a[], int size) {
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

/**  Find minimum sliding window size (INT_QUEST)
 * e.g. array[7] ={ 1, 0, -1, 2, 1, 0, -2 } ,swSize = 3
 * Windows ===> { 1, 0, -1 } = 0 { 0, -1, 2} = 1 { -1, 2, 1} = 2 { 2, 1, 0} = 3 {1, 0, -2} = -1
 * m >= swSize*2
 */
int findMinSlideSizeHelper(int arr[], int m, int swSize) {
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
int findMinSlideSize(char *str, int n) {
	/* TBD parse A and convert as Array */
	int a[] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
	int m = sizeof(a)/sizeof(a[0]);

	printf("Minimum slide size is %d\n",findMinSlideSizeHelper(a, m, n));

	return 0;
}

/* Find number of slots remaining in a theatre row, you can't place no 
 * two people next to each other
   Eg: [100000111] is input data->output is "2" as you seat two people
   like[101010111]
   Eg: 1010101000 -> 1010101010 ====> 1 person
   Eg: 0001010001 -> 0101010101 ====> 2 person
*/
int findSlotsHelper(int a[] ,int size) {
	int slot = 0;
	int i=1;
	while (i < size) {
	  if (a[i]) {
	    i++;
	  } else {
	    if (!a[i-1] && (i<size && !a[i+1])) {
		slot++;
		i++;
	    }
	  }
	  i++;
	}
	return slot;
}
int findSlots(char *str) {
	/* TBD parse A and convert as Array */
	int a[] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
	int m = sizeof(a)/sizeof(a[0]);
	printf("Number of people to fill %d\n",findSlotsHelper(a, m));

	return 0;
}

/** Find duplicates in a array using bitmask INT_QUEST
 *Use bitmask where each bit represents number 
 *TBD:Optimize this to decrease size of bitmask
 **/
void printDuplicatesHelper(int *arr, int len) {
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
int printDuplicates(char *str) {
	/* TBD parse A and convert as Array */
	int a[] = {1, 2, 3, 4, 1, 5, 7, 7, 4};
	int m = sizeof(a)/sizeof(a[0]);
	printDuplicatesHelper(a, m);

	return 0;
}

/* Print val without using print and using put */
void printwithputHelper(int val) {
	int rem;
	if (val) {
		rem = val %10;
		printwithputHelper(val/10);
		putc(rem + '0', stdout);
	} 
}
int printwithput(char *str) {

	printwithputHelper(myAtoi(str));
	return 0;
}

/* Wrappers for testType -> function */
typedef int (*fptr1) (char *str);
typedef int (*fptr2) (char *str, int len);
typedef struct testToRun {
	char *testType;
	int params;
	fptr1 func1;
	fptr2 func2;
	char *descr;
}testRun;

/* testRun tests[] will be used for invoking corresponding tests */
static testRun tests[] = {{"duplicates", 1, printDuplicates, NULL, "Print Duplicates in A[]"},
	           {"minSlide", 2, NULL, findMinSlideSize, "find minimum slide in A[] with slide size n"},
		   {"putPrint", 1, printwithput, NULL, "Print n using put"},
		   {"findSlot", 1, findSlots, NULL, "Movie theatre slot problem"}
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
void start_arraytest(int argc, char *argv[]) {
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
			if (ptr->params == 1)
				(*ptr->func1)(argv[3]);
			else
				(*ptr->func2)(argv[3], myAtoi(argv[4]));
		}

	}

	if (not_found) {
		usage(argc, argv);
		return;
	}
}
