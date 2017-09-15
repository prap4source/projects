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
