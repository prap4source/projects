/* C code for misc and mixed usage */
/* Check if key is present in hashtable
 * if get(k) is not '\0' return(v)
 * else set(k, md5(k))
 */
#include "common.h"
char *check_hash_for_md5(char *key) {
     char *value = getHash(key);
     if (value != '\0')
	    return value;
     else {
	 value = calc_md5(key);
	 if (value != NULL) {
	     setHash(key, value);
	     free(value);
	 }
     }
     return (char *)NULL;
}

/* 
llist of integer (unsorted)
bool lookup(int key)
void delete(int key)
highly concurrent of lookup/delete, lookup/lookup, delete/delete

lookup - 0(1)
use hash
typedef struct hashEntry {
  int key;
  int *location;
  struct hashEntry *next;
} *hashEP;
hashEP table[MAX];
bool lookup (int key) {
  hashEP temp= table[key%MAX];
   if (temp != NULL) {
    unlock();
    return true;
  } else {
    unlock();
    return false; 
  }
}

||HEAD1||->>>>>>>>>>>>>>>>>>>>(key10)
||HEAD2||->>>>>>>>>>>>>>>>>>>>(key11)

void delete(int key) {
  
}*/
