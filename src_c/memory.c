/*
 * memory.c
 *
 *  Created on: Sep 15, 2017
 *      Author: Pradeep Gopanapalli
 */
#include "common.h"
/* Write a function that pads a sequence of bytes to a multiple of a given block length.
Requirements:
* The value of each added byte should be the total number of added bytes.
  (N bytes, each of value N are added.)
* If the original sequence is a multiple of N bytes, an extra block of N bytes is added.

Example (for block length 16)
* 12 bytes, must be padded to 16 bytes, 4 bytes padding, 0x04 in each byte padded
* 24 bytes, must be padded to 32 bytes, 8 bytes padding, 0x08
* 31 bytes, must be padded to 32 bytes, 1 byte padding, 0x01
* 38 bytes, block length is a multiple of 3 bytes, must be padded to 39 bytes 1 <0x01
* 36 bytes, block length is a multiple of 3 bytes, must be padded to 39 bytes 3 <0x03
* size is size of block ,padto is number of bytes to pad 
padto = (size < block) ? (block -size) : (block - size % block);
func_padto(bytes,size,padto)
char *func_padto(char *bytes, int size, int padto) {
    int val = padto;
    char *newBytes = realloc(bytes, size + padto);
    for (int i =0 ;i <padto; i++)
        *(char *)(newBytes + size + i) = val;
   return newBytes; // Padding to padto 
} */

/* Allocate aligned  memory ,Use a extra space at front of memory to store offset */
void *amalloc(int size, int alignment) {
    void *mem, *ptr;
    int offset = (alignment - 1) + sizeof(char); /*sizeof(char) for storing information */

    mem = malloc (size + offset );
    printf("%p \n",mem);
    ptr=(void**) (((size_t)(mem) + offset) & ~(alignment -1));
    *(char *)(ptr - sizeof(char)) = (ptr - mem);
    return ptr;
}

/* Free aligned  memory ,this routine will be ptr to data memory so we need to find 
   actual memory starting */
void afree(void *ptr) {
	int  off = *(char *)(ptr - sizeof(char));
	printf ("%p \n",ptr-off);
	free(ptr - off);
}
