/* Implement hashing  
 * Handle Collision -> done
 * String hash -> TBD
 * Removal procedure -> TBD*/
#include "common.h"

/* hash(key,value) where key is integer value is string */
typedef struct hashe{
	char *key;
	char *value;
	struct hashe *next;
} hashentry, *hashEntryp;

typedef struct hasht {
	hashEntryp table;
	int max_entries;
	int tot_entries;
} hashtable, *hashTablep;

typedef struct dict {
	char *k;
	char *v;
} dict_e;
dict_e myDict[] = {{"zoo","keeper"}, {"play","cricket is life"}, {"oracle","is cloud"},{"google", "search"}, 
		   {"amazon","big player"}, 
		   {"amazon","another comp"}};

hashTablep projtable;
void hash_init(int entries) {
	projtable = calloc(1, sizeof(hashtable));
	projtable->max_entries = entries;
	projtable->table = calloc(entries, sizeof(hashentry));
}

void hash_fini() {
	printf ("\n total Entries %d \n",projtable->tot_entries);
	int i = projtable->max_entries-1;
	for (; i>=0; i--) {
		hashEntryp entry = &projtable->table[i];
		if (entry->value) {
			log ("Top Free(%s,'%s') \n",entry->key, entry->value);
			free(entry->value);
			free(entry->key);
			entry = entry->next;
			while (entry) {
				hashEntryp temp = entry->next;
				if (entry->value != NULL) {
					log ("Free(%s,'%s') \n",entry->key, entry->value);
					free(entry->value);
					free(entry->key);
				}
				free(entry);
				entry = temp;
			}
		}
	}
	free(projtable->table);
	free(projtable);
	projtable = NULL;
}
/* h(s)=s[0]*31^(n-1) + s[1]*31^(n-2) + ... + s[n-1] 
 http://grepcode.com/file/repository.grepcode.com/java/root/jdk/openjdk/6-b14/java/lang/String.java#String.hashCode%28%29
 http://stackoverflow.com/questions/15518418/whats-behind-the-hashcode-method-for-string-in-java
 */ 
int hashCode(char *val) {
	int  hash = 0;
	for (int i =0; i< strlen(val); i++)
		hash = ((31 * hash) + val[i]) % projtable->max_entries;
	return (hash % projtable->max_entries);
}

char *getHash(char *key) {
	int hash = hashCode(key);
	hashEntryp entry = &projtable->table[hash];
			 
	while (entry && (entry->value != '\0')) {
		if (strcmp(entry->key, key) == 0) {
			log("entry(%s:%s)\n", entry->key, entry->value);
			return entry->value;
		}
	       entry = entry->next;
	}
	log ("key%s hash%d not present \n", key, hash);
	return (char *)'\0';
}
	
void setHash(char *key, char *val) {
	int hash = hashCode(key);
	hashEntryp entry = &projtable->table[hash], new_entry;
	/* already present */
	if (entry && (entry->value != NULL)) {
		log("hash(%d,'%s')  present \n",hash, entry->value);
		while (entry->next) entry = entry->next;
		entry->next = malloc(sizeof(hashentry));
		entry = entry->next;
	}
				
	entry->value = malloc(strlen(val) + 1);
	entry->key = malloc(strlen(key) + 1);
	strcpy(entry->value, val);
	strcpy(entry->key, key);
	entry->next = NULL;
	log("entry(%d,'%s') key:%s\n",hash, entry->value,key);
	projtable->tot_entries++;
}
void printHash() {
	int i;
	for (i=0; i < projtable->max_entries; i++) {
		hashEntryp entry = &projtable->table[i];
		printf("\n ===Hash(%d)====\n", i);
		while (entry) {
			if (entry->value != NULL)
				printf (" entry(%s,'%s') " ,entry->key, entry->value);
			entry = entry->next;
		}
		
	}
}

void start_hprogram() {
	int i =0, size;
	hash_init(MAX_HASH);
	size = sizeof(myDict)/sizeof(myDict[0]);
	for (dict_e *temp = myDict; temp != myDict + size; temp++) {
		setHash(temp->k, temp->v);
	} 
	for (int i =0; i< size;i++) {
		char *p = getHash(myDict[i].k);
		if (p != NULL)
			printf("get(%s):'%s' \n", myDict[i].k, p);
	}
	printHash();
	hash_fini();
}
