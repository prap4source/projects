#include "common.h"
#include "operations.h"
#include "bitsops.h"
/* fptr is function pointer */
typedef int (*fptr) (int);
typedef struct strfunc {
    char *str;
    fptr func;
}sfunc;
		    
/* (INT_QUEST)Set bits between two indexes You are given two 32-bit numbers, N and M, and two bit positions, i and j 
 *  Write a method to set all bits between i and j in N equal to M (e g , M becomes a substring of N located at i and starting at j)   
    EX:N = 10000000000, M = 10101, i = 2, j = 6 Output: N = 10001010100
    This code operates by clearing all bits in N between position i and j, and then OR to put M in there */
int updateBits(int N, int M, int i, int j) {
   	int max = ~0; /* All 1’s */
   	// 1’s through position j, then 0’s
   	int left = max - ((1 << j) - 1);
   	// 1’s after position i
   	int right = ((1 << i) - 1);
  	// 1’s, with 0s between i and j
  	int mask = left | right;
  	// Clear i through j, then put m in there
  	return (N & mask) | (M << i);
  }
/* 
 * (INT_QUEST) find blocks of 1 in a number
 * Eg: 11001110101111 returns 4 as there are 4 blocks
 */
int findBlocksofone(int num) {
    int blocks =0 , bits =0;
    while (num) {
	if (!(num & 0x1)) {
	    if (bits) blocks++;
	    bits = 0;
	} else bits ++;
	num = num >> 1;
    }
    /* For MSB block */
    if (bits) blocks ++;
    return blocks;
}

int modifybits(int num) {
    int flag;
    int *addr = calloc(1, 4 * sizeof(int));
    int ret =0;
    printf("Enter bit to set ?\n");
    scanf("%d", &flag);
    *addr = num;
    set_bit(flag, (ulong *)addr);
    printf("setbit(%d:%p) num(%d:%d)\n",flag, addr, num ,*addr);
    ret = *addr;
    free(addr);
    return (ret);
}
/* set l to r bits in y ,if they are set in x
 * int n =  set_bit_l_to_r(25,32,4,3); -> return 48
 */
int set_bit_l_to_r(int x, int y, int l , int r) {
    if ((l < r) || (l-r <-1))
	return y;
    /* Mask will be bits from l to r in x */
    int mask = x & (((1<<(l-r+1))-1) <<l);
    
    return (y | mask);
}

/* Brian Kernighan’s Algorithm: Subtraction of 1 from a number toggles all the bits (from right to left) 
   till the rightmost set bit(including the righmost set bit). So if we subtract a number by 1 
   and do bitwise & with itself (n & (n-1)), we unset the righmost set bit. 
   If we do n & (n-1) in a loop and count the no of times loop executes we get the set bit count.
   Beauty of the this solution is number of times it loops is equal to the number of set bits 
   in a given integer.
   http://www.geeksforgeeks.org/count-set-bits-in-an-integer/
*/
int countbits(int n) {
    int count = 0;
    while (n) {
        n &= (n-1);
        count++;
    }
    return count;
}
/* Brute Force way */
int countbits1(int n) {
    int count = 0;
    while (n) {
        count += (n &0x1);
        n >>= 1;
    }
    return count;
}

/* get sum of a & b without +/- */
int getSum(int a, int b) {
        while (b) {
            int temp = a;
            a = a ^ b; /* exclusive or of a & b */
            b = (temp & b) << 1; /*carry forward */
        }
        return a;
}

/* The Hamming distance between two integers is the number of positions at which 
the corresponding bits are different.Given two integers x and y, calculate the Hamming distance.
Example: Input: x = 1, y = 4 Output: 2
Explanation:
1   (0 0 0 1)
4   (0 1 0 0)
       ↑   ↑
The above arrows point to positions where the corresponding bits are different. 
https://leetcode.com/problems/hamming-distance/
*/
int FindHammingDistance(int x, int y) {
        int z = x^y;
        return (countbits(z));
}

/* Write a program to get length of  the Longest Consecutive 1s in Binary Representation 
   Method1*/
int maxConsecutiveOnes1(int a)
{
    int length, max_seq ;
    length = max_seq = 0;
    while (a) {  
     	if (a & 0x1) {
        	length ++;
    	} else {   	
       	length = 0;
  	    }
        max_seq = max (max_seq, length);
      a >>= 1;
    }  
     return max_seq;
}

/*  Write a program to get length of  the Longest Consecutive 1s in Binary Representation 
   Method2 Using Bit Magic: The idea is based on the concept that if we AND a bit sequence with a shifted version of itself, we’re effectively removing the trailing 1 from every sequence of consecutive 1s.
     11101111   (x)
    & 11011110   (x << 1)
    ----------
      11001110   (x & (x << 1)) 
        ^    ^
        |    |
   trailing 1 removed
   So the opeation x = (x & (x << 1)) reduces length of every sequence of 1s by one in binary representation of x. If we keep doing this operation in a loop, we end up with x = 0. The number of iterations required to reach 0 is 
   actually length of the longest consecutive sequence of 1s.*/
int maxConsecutiveOnes2(int a)
{
    int max_seq = 0;
    while (a) {
        a = (a & (a <<1));
        max_seq++ ;
    }   
    return max_seq;
}

/* Write a program to reverse bits in a number 
reverseBits( 232, 5 , 4) will reverse 4 bits starting from 5th position
232 - 1110 1000 
Result : 212 - 1101 0100 
For bit problems we need to form  a bit mask first , here the bit mask is 
n number of 1’s shifted to m th position
In this case 1111 shifted to 5th position i.e 00111100 ^ number
 Prepare a mask with 1's from m to n and Ex-or with num */
int reverseBitsmton(int num, int m ,int n){
	int max = ~0;
	int mask;
	/* Prepare n number of 1's */
	mask = ~(max << n);
	/* Shift to m location */
	mask <<= (m-n+1);
	return (num ^ (mask));
}
/* Given a number 11 (1011) reverse bits 1101 
https://discuss.leetcode.com/topic/9863/my-3ms-pure-c-solution */
int reverseBits(int n) {
        int m = 0;
        for (int i =0 ;i <32;i++,n>>=1) {
            m <<= 1;
            /* Like a circle */
            m = m | (n&0x1);
        }
        return m;
}
/* Given a number 101 -> find complement 010 without trailing zeros
https://leetcode.com/submissions/detail/94678943  */
int findComplement(int num) {
        int mask = ~0;
        if (!num)
            return 1;
        while (num & mask) mask <<=1;
        return (~num & ~mask);
}

/*Given an array of integers, every element appears three times except for one, which appears exactly once. Find that single one.
    Note:
    Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory? 
    Logic: Use a bit mask to count bits set for each position of bit and modulus by 3
*/
int singleNumberIII(int* nums, int numsSize) {
    long long int bits[32] = {0};
    int result =0;
    
    for (int i =0; i<numsSize; i++) {
    /* Count number of set bits*/
        for (int j=0; j< 32; j++) {
            if (nums[i] & (1<<j))
                bits[j]++;
        }
    }
    
    for (int j=0; j<32;j++) {
        if (bits[j] % 3)
            result |= (1<<j);
    }
    
    return result;
}

char *convertTobits(int num) {
    int size = sizeof(num)* 8, i;
    char *str = malloc(size + 1); /*33 bits */
    for (i = 0; i < size; i ++) {
	int bitmask = 1U << (((size-1)-i) % BITS_PER_INT);
	if (num & bitmask)
	    str[i] = '1';
	else 
	    str[i] = '0';
    }
    str[size] = '\0';

    return str;
}

sfunc bitTable[] = {{"findblocks", findBlocksofone},
		    {"reversebits", reverseBits},
		    {"countbits", countbits1},
		    {"modbits", modifybits}};

void start_bittests(int argc, char *argv[]) {
    bool not_found = true;
    int sizes = sizeof(bitTable)/sizeof(bitTable[0]);
    if (argc == 4) {
	int num = myAtoi(argv[3]);
	char *p = convertTobits(num);
	sfunc *tempTable;
	for (tempTable = bitTable; tempTable != bitTable + sizes; tempTable++) {
	    if (!strcmp("all", argv[2]) || !strcmp(tempTable->str, argv[2])) {
		int n = tempTable->func(num);
		char *p1 = convertTobits(n);
		printf("%s(%s) input(%d:%s)::output(%d:%s) \n", tempTable->str, argv[3], num, p, n, p1);
		not_found = false;
		free(p1);
	    }
	}
	free (p);
    } 
    if (not_found) {
	    printf ("Usage %s <%s> <",argv[0], argv[1]);
	    for (int i = 0; i < sizes; i++) 
		    printf("%s|", bitTable[i].str);
	    printf("> <val>\n");
    }

}

