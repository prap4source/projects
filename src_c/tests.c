/* Some coding challenges asked in interviews */
#include "common.h"
#include <stdlib.h>
/* Find size of variable and type */
#define sizeof_var(a) ((size_t)(&(a) + 1)-(size_t)(&(a)))
#define sizeof_type(T) ((size_t)((T*)1000 + 1) - (size_t)((T*)1000))
/* Find max of (x,y) */
#define max(x,y) ((x)>(y)?(x):(y))
/* Find min of (x,y) */
#define min(x,y) ((x)<(y)?x:(y))

int findMaxinArray(int *arr, int len) {
	int max_no = arr[0], i;
	for (i=1; i < len ;i++) {
		max_no = max(max_no, arr[i]);
	}
	return max_no;
}
/** Find duplicates in a array using bitmask
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
/* https://www.careercup.com/question?id=14424684 */
char *read4k(char *buf, int num) {

	return NULL;
}

void start_test(int argc, char *argv[]) {
	int a[] = {1,4,2,1,0,pow(2,31)-1,0,pow(2,31)-1};
	printDuplicates(a, sizeof(a)/sizeof(a[0]));
	log ("num of arguments %d \n",argc);

	if (argc >= 4) {
		char *result = multiplyStrings(argv[2], argv[3]);
		log ("(%s:%s)", argv[2], argv[3]);
		if (result) {
			printf("mulitply(%s:%s) is %s \n", argv[2], argv[3], result);
			free(result);
		}
	}
}
	


