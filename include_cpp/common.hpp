#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#ifdef DEBUG
#define log_info printf
#else 
#define log_info(fmt, ...) {}
#endif
#define MAX_HASH 1000
