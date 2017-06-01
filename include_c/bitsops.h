/* Operations on bits */
#ifdef set_bit
#undef set_bit
#undef test_bit
#define BITS_PER_LONG 64
#define BITS_PER_INT 32
#define BIT_MASK_L(nr) (1UL << (nr % BITS_PER_LONG)) 
#define BIT_WORD_L(nr) (nr / BITS_PER_LONG)
static int misc_bits(int num, int position) {
    int v;
    num = num | (1 << position);/* Program to set a particular bit in an integer */
    num = num & ~(1 << position); /* Program to clear a particular bit in an integer */
    num = num ^ (1 << position); /* Program to toggle a particular bit */
    if (num & (1 << position) == 1) /* Program to check whether a bit is set or not */
	return 1;
    if (num & (1 << position) != 1) /* Program to check whether a bit is clear or not */
	return 1;
    if (num & (num - 1) == 0) /* Program to check whether a number is power of 2 or not */
	return 1;
    num= (num << 3) - num; /* Program to multiply a number by 7 without using a multiply */
    v =  v && !(v & (v - 1)); /* Note that 0 is incorrectly considered a power of 2 here */
    return 0;
}
/* http://elixir.free-electrons.com/linux/latest/source/include/asm-generic/bitops/non-atomic.h#L103 */
static int test_bit(int flag, uint64_t *addr) {

    return 1UL & (addr[BIT_WORD_L(flag)] >> (flag & (BITS_PER_LONG -1)));
    
}

static int set_bit(int nr, uint64_t *addr) {
    uint64_t *p = ((uint64_t *)addr + (nr / BITS_PER_LONG));
    printf("(%d:%d:%d) \n",nr, (nr >> 5), 1<< (nr&31)); /* o/p == (35:1:3) */
    printf("(%x:%x) \n",addr, p);
    return 0;

}
#endif
