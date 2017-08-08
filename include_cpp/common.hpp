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
 #define app_type(type) 	\
 void start_##type(int argc, char *argv[]); \

 app_type(slist)
 app_type(hash)
 app_type(stests)
 app_type(puzzles)
 app_type(classes);


 /* fptr is function pointer which takes void and returns void */
 typedef void (*fptr)(int argc, char *argv[]);
 typedef struct scase {
	 const char *str;
	 fptr func;
 }stringcase;
 /* Dictonary of string to function pointers */
static stringcase myCases[] = {{"hash", start_hash},
			 {"string", start_stests},
			 {"puzzles", start_puzzles},	
			 {"singlelist", start_slist},
			 {"lessons", start_classes}};

