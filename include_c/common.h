/*
 * common.h
 * Copyright 2017 Pradeep Gopanapalli 
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <math.h>
#include <limits.h>
#include <ctype.h>
#include <stdint.h>
#include <errno.h>

#ifdef DEBUG
#define log(fmt,...) printf("%s:%d::::"fmt"\n",__func__,__LINE__,## __VA_ARGS__)
#else
#define log(fmt, ...) { }
#endif
#define log_err(fmt,...) printf("%s:%d Error::::"fmt"\n",__func__,__LINE__,## __VA_ARGS__)
#define log_info(fmt,...) printf("%s:%d INFO::::"fmt"\n",__func__,__LINE__,## __VA_ARGS__)
#define func_def(type) void start_##type(int argc, char *argv[]);
#define MAX_HASH 10
#define MAX_QUEUE 5
#define MAX_SOCK_MSG 256

#define SUCCESS 0
/* Socket API's */
func_def(server);
func_def(client);
/* Run tests */
func_def(test);
/* Hash */
func_def(hprogram);
void hash_init();
void hash_fini();
char *getHash(char *key);
void setHash(char *key, char *value);
/* MD5 csum */
func_def(md5);
char *calc_md5(char *fileName);
char *check_hash_for_md5(char *key);
/* tests to run */
char *multiplyStrings(char *n1, char *n2);
int compareVersion(char *v1, char *v2);
int myAtoi(char *str);
void printDuplicates(int *arr, int len);
int findMinSlideSize(int arr[], int m, int swSize);
/* bit tests*/
func_def(bittests)
/* C basic tests */
func_def(cbatests)
/* single linked list */
func_def(llist);
/* Thread & synchronization  tests */
func_def(thrtests);
