/* Find size of variable and type */
#define sizeof_var(a) ((size_t)(&(a) + 1)-(size_t)(&(a)))
#define sizeof_type(T) ((size_t)((T*)1000 + 1) - (size_t)((T*)1000))
/* Find max of (x,y) */
#define max(x,y) ((x)>(y)?(x):(y))
/* Find min of (x,y) */
#define min(x,y) ((x)<(y)?x:(y))
extern long long int alloc_mem;
extern long long int freed_mem;

static void *my_malloc(int size) {
    alloc_mem ++;
    return (malloc(size));
}

static void my_free(void *mem) {
    freed_mem ++;
    free(mem);
    return;
}
