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
