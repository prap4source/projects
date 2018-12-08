/*
 * Copyright 2017 Pradeep Gopanapalli
 * arrayTests.c
 * Some coding challenges asked in interviews
 */
#include "common.h"
#include "operations.h"

/* convert string to array */
int *prepArrayHelper(char *str, int *len) {
	/* Caller will free memory */
	int *A = malloc(sizeof(int) * MAX_ELEMENTS);
	char *p = str;
	int size = 0, n = 0;
	char tmp[200000];

	if (A == NULL) {
		*len = 0;
		return NULL;
	}

	while ((*p != '\0') && (n < MAX_ELEMENTS)) {
		if (*p == ',') {
			A[n] = myAtoi(tmp);
			log ("n=%d A[n]=%d tmp=%s ", n, A[n], tmp);
			n++;
			memset(tmp, 0, size);
			size = 0;

		} else {
			log ("size=%d *p=%c ", size, *p);
		        tmp[size++] = *p;
		}
		p++;
		/* Fill last element */
		if (*p == '\0') 
			A[n++] = myAtoi(tmp);
	}


	if (n == MAX_ELEMENTS) {
		*len = 0;
	} else {
		*len = n;
	}

	return A;
}
int prepArray(char *str, int n) {
	int *tmp;
	int len = 0;
	
	printf("n=%d, str=%s \n", n, str);
	tmp = prepArrayHelper(str, &len);
	for (int i = 0; i < len; i++)
		printf("i=%d, element=%d \n",i, tmp[i]);
        
	free(tmp);
	return 0;
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

/* Find maximux in an array*/
int findMaxinArray(int *arr, int len) {
	int max_no = arr[0], i;
	for (i=1; i < len ;i++) {
		max_no = max(max_no, arr[i]);
	}
	return (max_no);
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

/* Find number of slots remaining in a theatre row, you can't place no 
 * two people next to each other
   Eg: [100000111] is input data->output is "2" as you seat two people
   like[101010111]
   Eg: 1010101000 -> 1010101010 ====> 1 person
   Eg: 0001010001 -> 0101010101 ====> 2 person
*/
int findSlots(int a[] ,int size) {
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

/** Find duplicates in a array using bitmask INT_QUEST
 *Use bitmask where each bit represents number 
 *TBD:Optimize this to decrease size of bitmask
 **/
int printDuplicates(int *arr, int len) {
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
	return 0;
}

/* Wrappers for testType -> function */
typedef int (*fptr1) (int *Array, int len);
typedef int (*fptr2) (int *Array, int len, int m);
typedef struct testToRun {
	/* Type of test*/
	char *testType;
	/* Number of parameters */
	int params;
	/* Function type ,0->fptr1&fptr2 1->fptr3*/
	fptr1 func1;
	fptr2 func2;
	char *descr;
}testRun;

/* testRun tests[] will be used for invoking corresponding tests */
static testRun tests[] = {{"duplicates", 1, printDuplicates, NULL, "Print Duplicates in A[]"},
	           {"minSlide", 2, NULL, findMinSlideSize, "find minimum slide in A[] with slide size n"},
		   {"findSlot", 1, findSlots, NULL, "Movie theatre slot problem"},
		   //{"prepArray", 2,  NULL, prepArray, "convert string to Array"},
		   {"findMax", 1, findMaxinArray, NULL, "Find Maximum in an Array"}
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
			int *arr;
			int m =0;

			/* Convert string to Array */
			arr = prepArrayHelper(argv[3], &m);
			if (m) {
				int result;
				if (ptr->params == 1)
					result = (*ptr->func1)(arr, m);
				else
					result = (*ptr->func2)(arr, m, myAtoi(argv[4]));
				printf("%s() str:%s result:%d \n", ptr->testType, argv[3], result);
			} else
				log_err("Unable to execute m=%d",m);

			free(arr);
		}
	}

	if (not_found) {
		usage(argc, argv);
		return;
	}
}
