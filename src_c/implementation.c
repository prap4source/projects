/*
 * implementations.c
 * Copyright 2017 Pradeep Gopanapalli 
 * 
 */
#include "common.h"
#include "bitsops.h"
/* cmpxchg 
 * if (*p == OLD)
 *      return false;
 * *p = NEW
 * return true;
 */
#define cmpxchg(P, O, N) __sync_val_compare_and_swap(P, O, N)
/* Compile read-write barrier */
#define barrier() asm volatile("": : :"memory")
/* Pause instruction to prevent excess processor bus usage */ 
#define cpu_relax() asm volatile("pause\n": : :"memory")

/* Implement spin_lock 
 * http://locklessinc.com/articles/locks/
 * https://github.com/cyfdecyf/spinlock 
 * */
typedef unsigned int spinlock;
void spin_lock_init(spinlock *lock) {
	*lock = 0;
}
void spin_lock(spinlock *lock) {
	while (!cmpxchg(lock, 0, 1)) {
		while (*lock)
			cpu_relax();
	}

}
void spin_unlock(spinlock *lock) {
	barrier();
	*lock = 0;
}
