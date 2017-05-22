/*
 * Stringtest.c
 */
#include "common.h"
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
