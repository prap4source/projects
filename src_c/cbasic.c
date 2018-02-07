/*
 * cbasic.c
 * Copyright 2017 Pradeep Gopanapalli 
 * 
 */
#include "common.h"
#include "bitsops.h"
#include <stdlib.h>
#include <stdio.h>

union p {
   int a;
   char b;
}k={1,25}; /* This will give Warning warning: excess elements in union initializer [enabled by default] */

void start_cbatests(int argc, char *argv[]) {
    int a = 10;
    int b = 20;
    /* read-only integers which means integers are not modifiable 
     *  c= 200 results error: cannot assign to variable 'd' with const-qualified type 'const int */
    const int c = 30;
    int const d = 40;
    
    /* ptr is pointer to const integer which means integer is not modifiable
     * but pointer is so *ptr = b will result in "error: read-only variable is not assignable" 
     */
    const int *ptr = &a;
    ptr++; /* allowed */
    
    /* ptr1 is constant pointer to int which means integer is modifiable but not pointer
     * so ptr++ or ptr1 = &a will result in " error: cannot assign to variable 'ptr1' with const-qualified type 'int *const'"*/
    int *const ptr1 = &a;
    *ptr1 = b; /* allowed */
    
    /* ptr2 is constanct pointer to constant integer which means neither integer or pointer is modifiable 
     * ptr2++ or *ptr2 = b results in "cannot assign" or "read-only variable" errors*/
    const int *const ptr2 = &a;
  
    printf("member of union %d \n",k.a); /*Prints 1 as it is the first value */

    
}


