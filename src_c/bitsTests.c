#include "common.h"
#include "operations.h"
typedef int EType;
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
EType countbits(EType n) {
    int count = 0;
    while (n) {
        n &= (n-1);
        count++;
    }
    return count;
}
/* Brute Force way */
EType countbits1(EType n) {
    EType count = 0;
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
Example:
Input: x = 1, y = 4
Output: 2
Explanation:
1   (0 0 0 1)
4   (0 1 0 0)
       ↑   ↑
The above arrows point to positions where the corresponding bits are different. 
https://leetcode.com/problems/hamming-distance/
*/
EType FindHammingDistance(EType x, EType y) {
        EType z = x^y;
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
uint32_t reverseBits(uint32_t n) {
        uint32_t m = 0;
        for (uint32_t i =0 ;i <32;i++,n>>=1) {
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
#if 0
void misc_bits() {
    uint32_t num;
    int position = 1,v;
    num = num | (1 << position);/* Program to set a particular bit in an integer */
    num = num & ~(1 << position); /* Program to clear a particular bit in an integer */
    num = num ^ (1 << position); /* Program to toggle a particular bit */
    if (num & (1 << position) == 1) /* Program to check whether a bit is set or not */
    if (num & (1 << position) != 1) /* Program to check whether a bit is clear or not */
    if (num & (num - 1) == 0) /* Program to check whether a number is power of 2 or not */
    num= (num << 3) - num; /* Program to multiply a number by 7 without using a multiply */
    v && !(v & (v - 1)); /* Note that 0 is incorrectly considered a power of 2 here */
}
#endif
void start_bittests(int argc, char *argv[]) {
    if (argc == 4) {
	int num = myAtoi(argv[3]);
	if (strcmp(argv[2],"findblocks") == 0) 
	    printf("%s(%d):%d \n", argv[2], num, findBlocksofone(num));
	else if (strcmp(argv[2], "reverseBits") == 0) 
	    printf("%s(%d):%d \n", argv[2], num, reverseBits(num));
    } else {
	    int n = 0x99;
	    printf ("countbits(%x): %x \n", n, countbits1(n));
    }
}

