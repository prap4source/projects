/*
 * Stringtest.c
 */
#include "common.h"
#include "operations.h"
/* Multiply integers represented as strings */
char *multiplyStrings(char *num1, char *num2) {
	char *num3;
    if (!num1 || !num2) {
        return NULL;
    }
    
    int l_1 = strlen(num1);
    int l_2 = strlen(num2);
    int i , j;
    int len = l_1 + l_2;
    
    num3 = (char *)calloc(1, len);
    log ("multiply(%s:%s) ",num1, num2);
    for (i = (l_1 - 1); i >= 0 ; i--) {
        int carry = 0;
        for (j =(l_2 - 1); j >= 0; j--) {
            int mul = (num1[i] - '0') * (num2[j] - '0') + carry + num3[i+j+1];
            num3[i+j+1] = (mul % 10);
            carry = (mul / 10);
            log ("num3 (%d,%d,%d) (%d,%d)\n",num3[i+j+1], carry, mul, i, j);
        }
        num3[i] += carry; 
    }
    int k = 0, t=0;
    /* Leave one digit for zero */
    while ((k < (len-1)) && (num3[k] == 0))
        k++; 
    
    char *ans = (char *)calloc(1, (len - k +1));
    for (; k < len ;k++) {
        log ("(%d:%d:%d:%d) \n", k, t, num3[k],len);
        ans[t++] = num3[k] + '0';
    }
    ans[t] ='\0';
    free(num3);
    return ans;
}


/* Given two non-negative integers num1 and num2 represented as string, return the sum of num1 and num2.
    Both num1 and num2 contains only digits 0-9. Both num1 and num2 does not contain any leading zero.
    You must not use any built-in BigInteger library or convert the inputs to integer directly.
    Logic: Start from end of the strings and add digits */

char* addStrings(char* num1, char* num2) {
    char *num3;
    int l1 = strlen(num1);
    int l2 = strlen(num2);
    int carry = 0;
    if (!l1)
        return num2;
    if (!l2)
        return num1;
    int size = max(l1,l2) +1; /* 1 for carry */
    int k;
    num3 = (char *)calloc(1, size);
    l1--;
    l2--;
    
    k = size-1;
    while ((l1 >= 0) || (l2 >=0)) {
        int sum = carry ;
        if (l1 >= 0) {
            sum += num1[l1] - '0';
            l1--;
        }
        if (l2 >= 0) {
            sum += num2[l2] - '0';
            l2--;
        }
        num3[k] = (sum %10) + '0';
        carry = (sum / 10);
        k--;
        
    }
    log("carry%d k%d size:%d) \n",carry, k, size);
    if (carry) {
        num3[k] = carry + '0';
        
        return num3;
    } else { /* readjust num3 */
        char *num4 = calloc(1, size);
        log ("k%d num3(%s) \n",num3, size);
        for (k=1;k<size;k++) {
            num4[k-1] = num3[k];
        }
        free(num3);
        return num4;
    }
}

/* Compare two versions like 1.2 , 1.13 and return 1 if version 1 is bigger 
 * and -1 if version1 is smaller or 0 
 */ 
int compareVersion(char* version1, char* version2) {
    int l1 = strlen(version1);
    int l2 = strlen(version2);
    int i =0 , j=0;
    while ((i < l1) || (j<l2)) {
        long long int num1=0, num2=0;
        while ((i<l1)&& version1[i] != '.') {
            num1 += num1*10 + (version1[i] - '0');
            i++;
        }
        while ((j<l2) && version2[j] != '.') {
            num2 += num2*10 + (version2[j] - '0'); 
            j++;
        }
        log("Sum(%lld:%lld) \n",num1,num2);
        if (num1 < num2) 
            return -1;
        else if (num1 > num2)
            return 1;
        if ((version1[i] != '\0') && (version1[i] == '.')) i++;
        if ((version2[j] != '\0') && (version2[j] == '.')) j++;
    }
    
    return 0;
}
/* atoi function convert string to integer 
 https://leetcode.com/problems/string-to-integer-atoi/#/description
 */
int myAtoi(char* str) {
    if (str == NULL)
        return 0;
    long long int i =0, len = strlen(str);
    int sign = 1, sum =0;
    
    while (str[i] != '\0' && str[i] == ' ')
            i++;
    if (str[i] != '\0') {
        if (str[i] ==  '+') {
            sign = 1;
            i++;
        } else if (str[i] == '-')  {
            sign = -1;
            i++;
        }
        while ((str[i] != '\0') && isdigit(str[i])) {
            int n = sum;
            sum = (sum * 10) + (str[i] - '0');
            if (sum/10 != n) {/* number too large or small */
                if (sign < 0)
                    return INT_MIN;
                else
                    return INT_MAX;
            }
            //log ("sum(%d) %d \n",sum, str[i]);
            i++;
        }
    
    }
    return (sign * sum);
}
