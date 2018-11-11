/*
 * implementations.c
 * Copyright 2017 Pradeep Gopanapalli 
 * 
 */
#include "common.h"
#include "bitsops.h"
#include <pthread.h>
/* cmpxchg 
 * if (*p == OLD)
 *      *p = NEW
 *      return true;
 * return false;
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
/* Implement rw locks of different types
rw_rlock(...) { ... }; <- as many readers but no writers
rw_wlock(...) { ... }; <- one writer ,no readers
rw_runlock(...) { ... };
rw_wunlock(...) { ... };
*/
struct rwlock
{
    pthread_mutex_t mtx;
    int readers;
    int writers;
    int count; /* Only for writer */
    pthread_cond_t  read_cv;
    pthread_cond_t write_cv;
};
void rw_wlock(struct rwlock *lock) {
    /* Hold mutex lock */
    /* check for count, if count != 0 wait and wakeup*/
        
    pthread_mutex_lock(&lock->mtx);
    while((lock->count != 0) || (lock->readers != 0)) {
              lock->writers++;
              pthread_cond_wait(&lock->write_cv, &lock->mtx);        
    }
    lock->writers--; 
    lock->count++;
    pthread_mutex_unlock(&lock->mtx);
}

void rw_wunlock(struct rwlock *lock) {
    pthread_mutex_lock(&lock->mtx);
    lock->count--;
    if (lock->writers) {
        pthread_mutex_unlock(&lock->mtx);
        pthread_cond_signal(&lock->write_cv);
    } else {
        pthread_mutex_unlock(&lock->mtx);
        pthread_cond_broadcast(&lock->read_cv);
    }
}

void rw_rlock(struct rwlock *lock) {
    /* Hold mutex lock */
    /* check for count, if count != 0 wait and wakeup*/
    pthread_mutex_lock(&lock->mtx);
    while((lock->count != 0))
        pthread_cond_wait(&lock->read_cv, &lock->mtx);
    lock->readers++;
    pthread_mutex_unlock(&lock->mtx);
}

void rw_runlock(struct rwlock *lock) {
    pthread_mutex_lock(&lock->mtx);
    lock->readers--;
    pthread_mutex_unlock(&lock->mtx);
    if (lock->writers)
        pthread_cond_signal(&lock->write_cv);
    else
        pthread_cond_broadcast(&lock->read_cv);
}

/* Fair lock also called ticket spinlocks 
 * Waiter will increment a counter and will wait until counter value corresponds to its turn, 
 * then it just needs to wait until that value appears. The result is called the ticket lock algorithm:
 * https://locklessinc.com/articles/locks/
 * https://nahratzah.wordpress.com/2012/10/12/a-trivial-fair-spinlock/
 */
typedef unsigned int uint;
#define atomic_add(P, V) __sync_fetch_and_add(P, V)
#define atomic_read(P) (*P)

typedef struct ticketlock_s{
	uint ticket;
	uint users;
} ticketlock;

void ticket_lock(ticketlock *lock) {
	uint my_ticket = atomic_add(&lock->users, 1);

	while (atomic_read(&lock->ticket) != my_ticket)
		cpu_relax();
}

void ticket_unlock(ticketlock *lock) {
	barrier();
	atomic_add(&lock->ticket, 1);
}
