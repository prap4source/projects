#include "hash.hpp"
void start_hash(int argc, char *argv[])
{
    HashTable first(MAX_HASH);
    
    for (int i =1;i<MAX_HASH * 50;i++) {
	    string s = "word";
	    s.append(to_string(i));
	    first.set(i,s);
    }

    for (int i =1;i<MAX_HASH*50;i++) {
	    if (!first.get(i).empty())
		printf("key%d     value%s\n",i, first.get(i).c_str());
	    else
		printf("Not available - key%d \n",i);
    }

    first.printhash();
}
