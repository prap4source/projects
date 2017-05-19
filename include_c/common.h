#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <math.h>

#ifdef DEBUG
#define log(fmt,...) printf("%s:%d::::"fmt"\n",__func__,__LINE__,## __VA_ARGS__)
#else
#define log(fmt, ...) { }
#endif
#define log_err(fmt,...) printf("%s:%d Error::::"fmt"\n",__func__,__LINE__,## __VA_ARGS__)
#define MAX_HASH 10
#define MAX_QUEUE 5
#define MAX_SOCK_MSG 256
/* Socket API's */
void start_server(int argc, char *argv[]);
void start_client(int argc, char *argv[]);
/* Hash start programs */
void start_hprogram(int argc, char *argv[]);
void hash_init();
void hash_fini();
char *getHash(char *key);
void setHash(char *key, char *value);
/* MD5 csum */
void start_md5();
char *calc_md5(char *fileName);
/* Misc */
char *check_hash_for_md5(char *key);
/* Run tests */
void start_test(int argc, char *argv[]);
