#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector> 
#include <string.h> 
#include <sstream> 
#include <stack>
#include <algorithm> 
#include <unordered_map>
#include <limits.h>

#ifdef DEBUG
#define log(fmt,...) printf ("%s:%d::::" fmt "\n",__func__,__LINE__,## __VA_ARGS__)
#else
#define log(fmt, ...) { }
#endif
#define log_err(fmt,...) printf ("%s:%d Error::::" fmt "\n",__func__,__LINE__,## __VA_ARGS__)

#define MAX_HASH 1000

/* function pointers for various Applications */
void start_hash(int argc, char *argv[]);
void start_stests(int argc, char *argv[]);
void start_puzzles(int argc, char *argv[]);
void start_slist(int argc, char *argv[]);
