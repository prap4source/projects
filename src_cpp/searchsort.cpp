/*
 * search&sort.cpp
 *
 *  Created on: Sep 15, 2017
 *      Author: pgopanap
 */
#include "common.hpp"
#include <algorithm>
#include <cmath>
using namespace std;
/* insert a element key j in already sort a[0:j-1] with swapping key to correct place */
void insertionSort(vector<int> &a, int size) {
    int i = 1, j, k;
    for (i=1; i < size; i++) {
        k = a[i];
        j = i-1;
        while (j >=0 && a[j] >  k) {
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = k;
    }
}

/* Binary search Recursiv mid element is calculated and left & right adjusted accordingly */
int bsearch(int arr[], int l, int r, int x) {
    if (l<=r) {
        int mid = l + (r -l) / 2 ; /* To avoid overflow */
        if (x==arr[mid])
        	return mid;
        else if (x < arr[mid])
        	return bsearch(arr, l, mid-1, x);
        else
        	return bsearch(arr, mid+1, r, x);
    } else
    	return -1;
}
/* Binary search Non recursive  */
int bsearch_nonR(int arr[], int l, int r, int x) {
   int mid;
    while (l<=r) {
        int mid = (l + r) / 2;
        if (x == arr[mid]) return mid;
        else if (x < arr[mid])    r = mid - 1;
        else l = mid + 1;
    }
    return -1;

}

/* Given a array with sorted negative values [-3,-2,0,1,4] sort
array with square of the numbers - [0,1,4,9,16] */
void insertionSortSquare(vector<int> &a, int size) {
    int i,j,k;
    a[0] = pow(a[0],2);
    /* sort in descending order */
    for (i=1; i <size; i++) {
        k = a[i];
        a[i] = pow(a[i],2);
        /* No need as negative squares will be in descending */
        if (k < 0) continue;
        k = a[i];
        j = i-1;
        while(j >=0 && a[j] < k) {
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = k;
    }
    reverse(a.begin(), a.end());
}
