/* Program for simple hash of strings 
http://www.algolist.net/Data_structures/Hash_table/Simple_example 
https://gist.github.com/tonious/1377667
*/
#include "common.hpp"
/* Program for simple hash of strings */
using namespace std;
class HashEntry {
    private:
	int key;
	string value;
	HashEntry *next;
    public:
	HashEntry(int k, string v): key(k), value(v) {next = NULL;}
	int getKey() {
	    return key;
	}
	void setKey(int k){
	    key = k;
	}
	string getValue() {
	    return value;
	}
	void setValue(string v) {
	    value = v ;
	}
	HashEntry *getNext() {
	    return next;
	}
	void setNext(HashEntry *n) {
	    next = n;
	}
};
class HashTable {
    private:
	HashEntry **table;
	int max_size;
	/* Hash generator */
	int getHash(int k) {
	    return (k%max_size);
	}
    public:
    void printhash() {	
		for (int i = 0;i <max_size; i++) {
			printf("\n =====hash(%d)========>\n", i);
			if (table[i] != NULL) {
			    HashEntry *entry = table[i];
			    while (entry->getNext()) {
				printf(" (%d,'%s') ", entry->getKey(), 
					(entry->getValue().c_str() != NULL) ? entry->getValue().c_str(): "NA" );
				entry = entry->getNext();
			    }
			}
			
		}
	}
    HashTable(int m) {
	    max_size = m;
	    table = new HashEntry * [max_size];
	    log_info ("size %d\n", sizeof(HashEntry*[max_size]));
	    for (int i = 0;i <max_size; i++)
		    table[i] = NULL;
    }
    ~HashTable() {
		for (int i = max_size-1; i>=0 ;i--) {
			HashEntry *entry = table[i];
			while (entry != NULL) {
				HashEntry *temp  = entry->getNext();
				delete entry;
				entry = temp;
			}
		}
		delete[] table;
		table = NULL;
    }
    string get(int key) {
	    int hash = getHash(key);
	    HashEntry *entry = table[hash];

	    while (entry) {
			if (entry->getKey() == key) {
				log_info ("'%s': get(%d) hash:%d present\n", entry->getValue(), key, hash);
				return entry->getValue();
			}
			entry = entry->getNext();		
	    }
	    log_info ("get(%d) hash:%d not present\n",key, hash);
	    return "";
    }
    void set(int key, string value) {
	    int hash = getHash(key);
	    HashEntry *newentry = new HashEntry(key, value);
	    HashEntry *entry = table[hash];
	    /* If entry is already used then chain it */
	    if (entry != NULL) {
			log_info ("set(%d:'%s') %d:hash already in use \n",
				key, value.c_str(), hash);
			while (entry->getNext()) entry = entry->getNext();
			entry->setNext(newentry);
	    } else {
			table[hash] = newentry;
	    }
	    
	    log_info ("set(%d,'%s') hash:%d done  \n",key, value.c_str(), hash);
    }
};
		
	

