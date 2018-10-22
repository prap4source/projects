#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;
#define ALPHABET 26
typedef struct trie {
    bool is_leaf;
    struct trie *next[ALPHABET];
}Trie;

/** Initialize your data structure here. */
Trie* trieCreate() {
    Trie *root = (Trie *)malloc(sizeof(Trie) );
    if (root) {
        int i;
        for (i =0;i<ALPHABET;i++)
            root->next[i] = NULL;
        root->is_leaf = false;
    }
    return root;
}

/** Inserts a word into the trie. */
void trieInsert(Trie* obj, string word) {
    Trie *temp = obj;
    int len = word.length();
    for (int i=0;i<len;i++) {
        int index = word[i] - 'a';
        if (temp->next[index] == NULL)
            temp->next[index] = trieCreate();
        temp = temp->next[index];
    }
    temp->is_leaf = true;
}

/** Returns if the word is in the trie. */
bool trieSearch(Trie* obj, string word) {
 Trie *temp = obj;
 int len = word.length();
 for (int i=0;i<len;i++) {
     int index = word[i] - 'a';
     if (temp->next[index] == NULL) 
        return false;
     temp = temp->next[index];
 }
 return ((temp !=NULL) && temp->is_leaf);
}

/** Returns if there is any word in the trie that starts with the given prefix. */
bool trieStartsWith(Trie* obj, string prefix) {
    Trie *temp = obj;
 int len = prefix.length(), i;
 for (int i=0;i<len && temp;i++) {
     int index = prefix[i] - 'a';
     temp = temp->next[index];
 }

 return temp;
}

void trieFree(Trie* obj) {
    Trie *temp = obj;
    for (int i=0;i<ALPHABET;i++) {
        Trie *temp;
        if (obj) {
            temp = obj->next[i];
            free(obj);
        }
        obj = temp;
    }
}

/* Trie program http://www.geeksforgeeks.org/trie-insert-and-search */
int start_trie(int argc, char *argv[]) {
  Trie* obj = trieCreate();
  // Input keys (use only 'a' through 'z' 
  // and lower case) 
  string keys[] = {"the", "a", "there", 
                    "answer", "any", "by", 
                     "bye", "their" }; 
    int n = sizeof(keys)/sizeof(keys[0]); 
  for (int i =0; i<n;i++)
        trieInsert(obj, keys[0]);
  bool param_2 = trieSearch(obj, keys[0]);
  bool param_3 = trieStartsWith(obj, keys[0]);
  trieFree(obj);
  return 0;
} 
