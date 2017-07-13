/* Find size of variable and type */
#define sizeof_var(a) ((size_t)(&(a) + 1)-(size_t)(&(a)))
#define sizeof_type(T) ((size_t)((T*)1000 + 1) - (size_t)((T*)1000))
/* Find max of (x,y) */
#define max(x,y) ((x)>(y)?(x):(y))
/* Find min of (x,y) */
#define min(x,y) ((x)<(y)?x:(y))
