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
 (TBD)(INT_QUEST) design a system which is highly concurrent to lookup/delete, lookup/lookup, delete/delete
 * list of integer (unsorted)
 * bool lookup(int key) , void delete(int key)
My Solution:
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
void delete(int key) {}
*/

/* (TBD)(INT_QUEST)  Design a polling function to check a adress (some address 0x12345) for a particular bit
 * My solution
 * int my_poll(void *p) {
 *    nv_priv *priv = (nv_priv)p;
 *    while (!test_bit(NV_IN_PROCESS, &priv->flag)) {
 * 	//wait
 * 	//yeild
 *   }
 *   return SUCCESS;
 * }
 * bool test_bit(int bit, int flag) {
 * 	if ((flag & (1<<bit))
 * 		return true;
 * 	return false;
 * }
 */
