/* Some coding challenges asked in interviews */
#include "common.h"
#include "bitsops.h"
#include <stdlib.h>


/* (TBD)(INT_QUEST)https://www.careercup.com/question?id=14424684 */
char *read4k(char *buf, int num) {

	return NULL;
}

void start_test(int argc, char *argv[]) {
	log ("num of arguments %d \n",argc);
	if (argc == 5) {
		if (strcmp(argv[2],"multiply") == 0) {
			char *result = multiplyStrings(argv[3], argv[4]);
			log ("(%s:%s)", argv[2], argv[3]);
			if (result) {
				printf("mulitply(%s:%s) is %s \n", argv[3], argv[4], result);
				free(result);
			}
		} else if (strcmp(argv[2], "compvers") == 0) {
			int result = compareVersion(argv[3], argv[4]);
			printf("compare(%s:%s) result%d\n", argv[3], argv[4], result);
		}
	} else if (argc == 4) {
	       if (strcmp(argv[2], "atoi") == 0) {
		       int result = myAtoi(argv[3]);
		       printf ("atoi(%s) == %d \n", argv[3], result);
	       } else if (strcmp(argv[2], "array") == 0) {
			int a[] = {1, 0, -1, 2, 1, 3, -2, -3, 0};
			int m = sizeof(a)/sizeof(a[0]);
			printDuplicates(a, m);
			printf("findMinSlideSize(%d) \n", findMinSlideSize(a, m, 3 ));
	      }
	} else {
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
}

