#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector> 
#include <string.h> 
#include <sstream> 

#ifdef DEBUG
#define log_info printf
#else 
#define log_info(fmt, ...) {}
#endif
#define MAX_HASH 1000

/* function pointers for various Applications */
void start_hash(int argc, char *argv[]);
void start_stests(int argc, char *argv[]);
