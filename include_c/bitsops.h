/* Operations on bits */
#ifdef __KERNEL__
#undef set_bit
#undef test_bit
#undef test_and_clear_bit
#undef test_and_clear_bit
#else 
#define  raw_local_irq_save(x) 
#define  raw_local_irq_restore(x)
#endif
#define set_bit my_set_bit
#define test_bit my_test_bit
#define test_and_clear_bit my_test_and_clear_bit
#define BITS_PER_LONG 64
#define BITS_PER_INT 32
#define BIT_MASK_L(nr) (1UL << (nr % BITS_PER_LONG)) 
#define BIT_WORD_L(nr) (nr / BITS_PER_LONG)
/* Set Prepare a bit mask to set bits b/w two bits High and low */
#define bit_mask_h_l(h, l) (((1<< (h-l+1)) -1) << l)

static inline int misc_bits(int num, int position) {
    int v;
    num = num | (1 << position);/* Program to set a particular bit in an integer */
    num = num & ~(1 << position); /* Program to clear a particular bit in an integer */
    num = num ^ (1 << position); /* Program to toggle a particular bit */
    if ((num & (1 << position)) == 1) /* Program to check whether a bit is set or not */
	return 1;
    if ((num & (1 << position)) != 1) /* Program to check whether a bit is clear or not */
	return 1;
    if (!(num & (num - 1))) /* Program to check whether a number is power of 2 or not */
	return 1;
    num= (num << 3) - num; /* Program to multiply a number by 7(2^3-1) without using a multiply */
    
    v =  v && !(v & (v - 1)); /* Note that 0 is incorrectly considered a power of 2 here */
    return 0;
}
#ifndef NONATOMIC_OP
/* http://elixir.free-electrons.com/linux/latest/source/include/asm-generic/bitops/non-atomic.h#L103 
 * test bit in given address*/

static inline int my_test_bit(int nr, unsigned long *addr) {
    unsigned long *p = ((unsigned long *)addr + (nr / BITS_PER_LONG));
    unsigned long bitmask = 1 << (nr % BITS_PER_LONG);
    unsigned long res = *p;
    
    return (res & bitmask) != 0;
    
}
static inline int my_test_and_clear_bit(int nr, unsigned long *addr) {
    ulong *p = ((ulong *)addr + (nr / BITS_PER_LONG));
    ulong bitmask = (1UL << (nr % BITS_PER_LONG));
    ulong flags;
    ulong old;
    raw_local_irq_save(flags); 
    old = *p;
    *p &= ~(bitmask);
    raw_local_irq_restore(flags);

    return (old & bitmask) != 0;
}

static inline int my_test_and_change_bit(int nr, unsigned long *addr) {

    ulong *p = ((ulong *)addr + (nr / BITS_PER_LONG));
    ulong bitmask = (1UL << (nr % BITS_PER_LONG));
    ulong flags;
    ulong old;
    raw_local_irq_save(flags); 
    old = *p;
    *p ^= (bitmask);
    raw_local_irq_restore(flags);
    return (old & bitmask) != 0;
}

static inline int my_test_and_set_bit(int nr , unsigned long *addr) {
	ulong *p = ((ulong *)addr + nr / BITS_PER_LONG);
	ulong bitmask = 1 << (nr % BITS_PER_LONG);
	ulong old;
	ulong flags;

	raw_local_irq_save(flags);
	old = *p;
	*p |= bitmask;
	raw_local_irq_restore(flags);
	
	return (old & bitmask) != 0;
}
	

static inline void  my_set_bit(int nr, unsigned long *addr) {
    unsigned long *p = ((unsigned long *)addr + (nr / BITS_PER_LONG));
    unsigned long bitmask = 1 << (nr % BITS_PER_LONG);
    unsigned long flags;
    raw_local_irq_save(flags);
    *p |= (bitmask);
    raw_local_irq_restore(flags);
}
#else
static inline void my_set_bit(int nr, ulong *addr) {
	(((ulong *)addr)[nr / BITS_PER_LONG]) |= 1 << (nr % BITS_PER_LONG);
}

static inline void my_clear_bit(int nr, ulong *addr) { 
	(((ulong *)addr)[nr / BITS_PER_LONG]) &= ~ (1<< (nr % BITS_PER_LONG));
}

static inline void my_test_bit(int nr, ulong *addr) {
	return ((((ulong *)addr)[nr / BITS_PER_LONG]) & (1 << (nr % BITS_PER_LONG))) != 0;
}
#endif
