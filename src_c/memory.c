/*
 * memory.c
 *
 *  Created on: Sep 15, 2017
 *      Author: Pradeep Gopanapalli
 */
#include "common.h"

void *amalloc(int size, int alignment) {
    void *mem, *ptr;
    int offset = (alignment - 1) + sizeof(char); /*sizeof(char) for storing information */

	mem = malloc (size + offset );
	printf("%p \n",mem);
	ptr=(void**) (((size_t)(mem) + offset) & ~(alignment -1));
	*(char *)(ptr - sizeof(char)) = (ptr - mem);
	return ptr;
}

void afree(void *ptr) {
	int  off = *(char *)(ptr - sizeof(char));
	printf ("%p \n",ptr-off);
	free(ptr - off);

}
