#include "common.hpp"
using namespace std;
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))
#define ARRAY_END(a)  (a+ ARRAY_SIZE(a))


/* Big-endian and little-endian are terms that describe the order in which a sequence  of bytes are stored in computer memory. 
Big-endian is an order in which the "big end" (MSB) is stored first (at the lowest storage 
address). Little-endian is an order in which the "little end"  (LSB) is stored first. */
void littleorbig() {
    int x = 1;
    if(*(char *)&x == 1)
      	printf("little-endian\n");
    else	
        printf("big-endian\n");
}

void printStaircase(int n) {
    string s;
    char space =' ';
    char hash ='#';
    
    for (int i =1;i<=n;i++) {
        string s;
        s.insert(0,(n-i),space);/* Position ,count copies, char or use s.append()*/ 
        s.insert((n-i),i,hash);
        cout<<s<<"\n";
    }
}
/*Given an array of integers, find if the array contains any duplicates. 
function should return true if any value appears  at least twice in the array, 
and it should return false if every element is distinct.
https://leetcode.com/problems/contains-duplicate/?tab=Description */
bool containsDuplicate(vector<int>& nums) {
        unordered_map<int, int> hash;
        if (!nums.size()) return false;
        for (auto it = nums.begin(); it != nums.end();it++) {
            if (hash[*it] ==1) return true;
            hash[*it] = 1;
        }
        return false;
}
/* Match parenthissis */
char match(char mt) {
        switch(mt) {
            case '(':
                return ')';
            case '{':
                return '}';
            case '[':
                return ']';
            default:
                break;
        }
        return (char)NULL;
    }
bool isValid(string s) {
        stack<char> st;
        for (auto c:s) {
            
            if ((c == '(')  || ( c =='{' )|| (c == '[' ))
                 st.push(c);
            else if ((c == ')') || (c =='}') || (c == ']')) {
                if (!st.size() || c != match(st.top()))
                        return false;
                st.pop();
            }
        }
        return !st.size();
    }
/* Given an array of integers where 1 ≤ a[i] ≤ n (n = size of array), some elements appear twice and others appear once.
Find all the elements of [1, n] inclusive that do not appear in this array.
Could you do it without extra space and in O(n) runtime? You may assume the returned list does not count as extra space.
Example:
Input:
[4,3,2,7,8,2,3,1]
Output:
[5,6]
https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/
*/
vector<int> FindMissingNumbers(vector<int>& nums) {
    vector<int> res;
    for (int i =0;i<nums.size();i++) {
        /* Use index to mark the numbers present */
        int index = abs(nums[i]) - 1;
        nums[index] = (nums[index] > 0) ? -nums[index] : nums[index];
    }
    
    for (int i =0;i<nums.size();i++) {
        if (nums[i] > 0) res.push_back(i+1); /* Which means i+1 numbers is not present */
        else nums[i] = abs(nums[i]); /*Convert back the nums */   
    }
    cout<<"\n Missing \n";
    return res;
}

/* Given an array of integers, 1 ≤ a[i] ≤ n (n = size of array), some elements appear twice and others appear once.
Find all the elements that appear twice in this array.
Could you do it without extra space and in O(n) runtime?
Example:
Input:
[4,3,2,7,8,2,3,1]
Output:
[2,3]
https://discuss.leetcode.com/category/568/find-all-duplicates-in-an-array
*/
vector<int> FindDuplicates(vector<int>& nums) {
    vector<int> res;
    for (int i =0;i<nums.size();i++) {
        int index = abs(nums[i]) - 1;
        /* If this is already indexed and not added to result */
        if ((nums[index] < 0) && 
            (std::find(res.begin(), res.end(),index+1) == res.end()))
            res.push_back(index+1);
        
        nums[index] = (nums[index] > 0) ? -nums[index] : nums[index];
    }
    
    /*Convert back the nums */
    for (int i =0;i<nums.size();i++) {
        nums[i] = abs(nums[i]);
    }
    cout<<"\n Duplicates \n";
    return res;
}


/* count maximum subsequence in a array 
   In  array of integers with negative values find maximum subsequence
   EX: {-2, -3, 4, -1, -2, 1, 5, -3} , maximum subseqence is from a[2] to a[6] 
   4 + -1 + -2 + 1 + 5 = 7 All we need is to ignore sub_sequence if it is less than 0 */
int findmaxSeq  (char a[], int size) {
	int this_seq, max_seq ,i;
	this_seq = max_seq =0;
	for (i=0; i< size ; i++) {
    	this_seq += a[i];
	    /* Compare only when  max_ending_here > 0 */
    	if (this_seq < 0)
        	this_seq = 0;
    	else
        	max_seq = max(max_seq, this_seq);
	}
	return (max_seq);
}

/* This program will find second largest number in a unsorted array  Logic is to 
   store first 2 numbers in ascending order ,and start comparing from 3rd element to N */
int find2ndLargest (int arr[], int N)
{
    int new_array [2];
    int i;
    /* Store first 2 elements in descending order */ 
    new_array[0] = (arr[0] > arr[1]) ? arr[0] : arr[1];
    new_array[1] = (arr[0] > arr[1]) ? arr[1] : arr[0];
    
    /* Traverse the remaining array and update new_array */
    for ( i= 2; i < N ; i++) {
        if (arr[i] > new_array[0]) {
            int tmp = new_array[0];
            new_array[0] = arr[i];
            new_array[1] = tmp;
        } else if (arr[i] > new_array[1])
            new_array[1] = arr[i];
            
    }
    return (new_array[1]);
}
/* Given a sorted array, remove the duplicates "in place" such that 
   each element appear only once and return the new length.
For example, Given input array nums = [1,1,2], and nums should be [1,2]
    Your function should return length = 2 
    https://leetcode.com/problems/remove-duplicates-from-sorted-array/?tab=Description */
int removeDuplicates(vector<int>& nums) {
        int prev;
        if (!nums.size()) 
            return 0;
        prev = nums[0];
        int i =1;
        for (int j = 1; j<nums.size();j++) {
            if (nums[j] != prev) {
                nums[i] = nums[j];
                prev = nums[j];
                i++;
            }
        }
        nums.resize(i);
        return i;
}


/* Rotate an array of n elements to the right by k steps.
For example, with n = 7 and k = 3, the array [1,2,3,4,5,6,7] is rotated to [5,6,7,1,2,3,4].
Logic here reverse 0,(n-k) and n-k to len and then reverse everything , o(n) time and o(1) space
https://leetcode.com/problems/rotate-array/?tab=Solutions
*/
void reversenums(vector<int>& nums, int start, int end) {
            while (start < end) {
                int temp = nums[start];
                nums[start] = nums[end];
                nums[end] = temp;
                start++;
                end--;
            }
}
void rotate(vector<int>& nums, int k) {
        int len = nums.size();
        k = k %len;
        if (!k)
            return;
        reversenums(nums, 0,(len-k)-1);
        reversenums(nums,len-k,len-1);
        reversenums(nums,0,len-1);
}

int findHistogram_Area(int H[],int W)
{
    int maxRec = 0;
    stack<int> St; 
    for(int w = 0; w < W; w++) { 
        if(St.empty() || H[w] >= H[St.top()]) {
            St.push(w);
        } else {
            int width, A;
            int h = H[St.top()];
            St.pop(); 

            if(St.empty()) width = w;
            else width = w - St.top();

            A = width * h;
            maxRec = max(maxRec, A);
        }
    }
    log("maxarea(%d) w%d",maxRec, W);
    return maxRec;
}

void start_puzzles(int argc, char *argv[]) {
    int arr[] = { 4,4,4,5,6,6,9,9,10};
    cout << "second highest" << find2ndLargest(arr,sizeof(arr)/sizeof(arr[0])) <<" \n";
    /* Find Duplicates */
    int arr1[] = {2, 1,4, 5, 2,4,1,2};
    vector<int> vecs(arr1,ARRAY_END(arr1));
    vector<int> result = FindDuplicates(vecs);
    for (int i = 0 ;i < result.size();i++) 
	cout <<result[i]<<"--";
    /* Find Missing*/
    result = FindMissingNumbers(vecs);
    for (int i = 0 ;i < result.size();i++) 
	cout <<result[i]<<"--";
    /* remove duplicates */
    vector<int> vecs2{arr,ARRAY_END(arr)};
    cout <<"\n New vector size "<<removeDuplicates(vecs2) <<"\n";
    /* Print new vector */
    for (auto i = vecs2.begin();i != vecs2.end();i++)
	cout <<*i<<"--";
    cout <<"\n";
    int hist[] = {1,4,5,8,9,20,3,5};
    int area = findHistogram_Area(hist, sizeof(hist)/sizeof(hist[0]));
    cout<<"Historgram Area is "<<area<<"\n";
    log ("Finished puzzles");
}

