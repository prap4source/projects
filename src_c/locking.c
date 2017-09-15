#if 0
struct mutex;
void mtx_lock(struct mutex *mtx);
void mtx_unlock(struct mutex *mtx);
struct condvar;
void cv_signal(struct condvar *cv);
void cv_broadcast(struct condvar *cv);
void cv_wait(struct condvar *cv, struct mutex *mtx);


struct rwlock
{
    struct mutex mtx;
    int readers;
    atomic_t writers;
    int count; /* Only for writer */
    struct condvar read_cv;
    struct condvar write_cv;
};
/*
rw_rlock(...) { ... }; <- as many readers but no writers
rw_wlock(...) { ... }; <- one writer ,no readers
rw_runlock(...) { ... };
rw_wunlock(...) { ... };
rw_wlock();
rw_wunlock();
Caller code
rw_rlock();
rw_runlock();
*/
void rw_wlock(struct rwlock *lock) {
    /* Hold mutex lock */
    /* check for count, if count != 0 wait and wakeup*/
        
    mtx_lock(&lock->mtx);
    while((lock->count != 0) || (lock->readers != 0)) {
              lock->writers++;
              cv_wait(&lock->write_cv, &lock->mtx);        
    }
    lock->writers--; 
    lock->count++;
    mtx_unlock(&lock->mtx);
}

void rw_wunlock(struct rwlock *lock) {
    mtx_lock(&lock->mtx);
    lock->count--;
    if (lock->writers) {
        mtx_unlock(&lock->mtx);
        cv_signal(&lock->write_cv);
    } else {
        mtx_unlock(&lock->mtx);
        cv_broadcast(&lock->read_cv);
    }
}

void rw_rlock(struct rwlock *lock) {
    /* Hold mutex lock */
    /* check for count, if count != 0 wait and wakeup*/
    mtx_lock(&lock->mtx);
    while((lock->count != 0))
        cv_wait(&lock->read_cv);
    lock->readers++;
    mtx_unlock(&lock->mtx);
}

void rw_runlock(struct rwlock *lock) {
    mtx_lock(&lock->mtx);
    lock->readers--;
    mtx_unlock(&lock->mtx);
    if (lock->writers)
        cv_signal(&lock->write_cv);
    else
        cv_broadcast(&lock->read_cv);

}

#endif
