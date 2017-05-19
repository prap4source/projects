/* API's for sharing memory across different processes */
void temp() {
#if 0
	projtable = mmap(NULL, sizeof(hashTablep), PROT_READ | PROT_WRITE, 
                    MAP_SHARED | MAP_ANONYMOUS, -1, 0);

	projtable->table = mmap(NULL, entries*sizeof(hashentry), PROT_READ | PROT_WRITE, 
                 MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	(entry) = mmap(NULL, sizeof(*entry), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

	entry->value = mmap(NULL, (strlen(val) + 1), PROT_READ | PROT_WRITE, 
                    MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	entry->key= mmap(NULL, (strlen(key)+1), PROT_READ | PROT_WRITE, 
                    MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	
	
	entry->next = mmap(NULL, sizeof(*entry->next), PROT_READ | PROT_WRITE, 
#endif
}

