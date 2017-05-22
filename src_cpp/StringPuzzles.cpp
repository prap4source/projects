#include "common.hpp"
using namespace std;
class S {
    public:
   /* Given a string "aabcccdddeffggggg" convert to a2b1c3d3e1f2g5 where each character 
       is displayed with how many times it is repeated*/
    string changeString(string s) {
        char tmp , prev;
        int i = 0;
        int c_n =1;
        prev = s[i++];
        
        while ( i < s.size()) {
            tmp = s[i];
            if (tmp == prev ) {
                s.erase(i,1);
                c_n++;
            } else {
                s.insert(i,to_string(c_n));
                c_n = 1;
                prev = tmp;
                i = i + 2;
            }
        }
        s.insert(i ,to_string(c_n));
        return (s);
    }
    /* Given an input string, reverse the string word by word. For example, 
       Given s = "the sky is blue", return "blue is sky the"
       https://leetcode.com/problems/reverse-words-in-a-string/?tab=Description */
       void reverseword(string &s,int i, int j) {
        while (i<j) {
            char temp = s[j];
            s[j] = s[i];
            s[i] = temp;
            i++;
            j--;
        }
    }
    int myatoi(const char* string)  {
	int value = 0; 
	if (string) {
	    while (*string && (*string <= '9' && *string >= '0'))
	    {
		value = (value * 10) + (*string - '0');
		string++;
	    }
	} 
	return value; 
    }
    
    /*strstr returns substring in a string */
    char *mystrstr(char *str, char *sub) {
	int len1=strlen(str);
	int len2=strlen(sub);
	
	if (len1 < len2)
	    return NULL;
    
	while ( len1 >= len2) {
	    len1--;
	    if (!memcmp(str,sub,len2))
		return str;
	    str++;
	}
    
	return NULL;
    }

    void reverseWords(string &s) {
        int i, j,l, words,len;
        len = s.length();
        i = j = l =words =0;
        char space = ' ';
        
        while (true) {
            /* Skip spaces at front */
            while ((i < len) && (s[i] == space)) {
                i++;
            }
            if (i == len)
                break;
            /* Add space for each word */
            if (words) s[j++] = space;
            l = j;
            
            while ((i<len) && (s[i] != space)) {
                s[j] = s[i];
                j++;
                i++;
            }
            //cout <<s<<"ONE"<<i<<j<<"\n";
            /* reverse each word */
            reverseword(s,l,j-1);
            words ++;
        }
        s.resize(j);
        /* Reverse entire sentence */
        reverseword(s,0,j-1);
    }
    /* reverse words in string there are no traling spaces and b/w words only one space*/
    void reverseWords1(string &s) {
        int i = 0,len = s.length(),words=0,l=0;
        char space =' ';
        while (true) {
            while ((i<len) && (s[i] !=space)) 
                i++;
            reverseword(s,l,i-1);
            l = i+1;
            words++;
            if (i==len)
                break;
            i++;
        }
        if (words)
            reverseword(s,0,len-1);
    }
    /* This Program finds largest subsequence without any character repetition in a string 
    Eg PRADEEPGOPANAPALLI Largest subsequence is 5 PRADE (0-4)
    Refer: 
    http://www.geeksforgeeks.org/length-of-the-longest-substring-without-repeating-characters 
    */
  
  int findLargeSS(string s) {
      vector<int> hash(256, -1);
        int index, curr, max_s;
        curr = max_s =0;
        for (int i =0;i<s.length();i++) {
            index = hash[s[i]];
            //cout <<"index is "<<index;
            if (index == -1 || ((i - curr)> index)) {/* If this is first time or character not part of current sequence */
                curr++;
            } else { /* repeated */
                max_s = max(max_s, curr); /* Sequence ends here */
                curr = (i - index);
            }
            hash[s[i]] = i;
            max_s = max(max_s, curr);
            //cout <<max_s<<curr<<index<<"\n";
        }
        return max_s;
  }
    /* This program converts given digits to currency format 
    Eg: 1234555 to 1,234,555 (comma before every 3 digits*/
    string convertTocurrency(string s) {
        int N = s.size();
        int i = 1, start = 0;
        char comma = ',';
        /* Best case */
        if (N <= 3) { 
            cout <<"String has "<<N <<" < elements \n";
            return s;
        }
        
        while (i<s.size()) {
            if (start || ((N%3) == (i % 3))) {
                start = 1;
                s.insert(i,1,comma);
                i += 4;
            } else i++;
        }
        return s;
    }

/* Given a string, find the first non-repeating character in it and return it's index. If it doesn't exist, return -1.
Examples: s = "leetcode" return 0. s = "loveleetcode", return 2 */
    int firstUniqChar(string s) {
        int  hash[256] = {0};
        /* Hash each element in string and increment each occurence */
        for (int i =0; i<s.size(); i++) 
            hash[s[i]] ++;
        
        for (int i=0; i<s.size(); i++) {
            if (hash[s[i]] == 1) 
                  return i;
        }
        return -1;
    }
    
/* Design an algorithm and write code to remove the duplicate characters in a string without using any additional bu er NOTE: 
   One or two additional variables are  ne An extra copy of the array is not */
void removeDups(string& s) {
    bool hash[256] = {false};
    int i = 0;
    while (i < s.size()) {
        if(hash[s[i]]) {
                s.erase(i,1);
        } else {
                hash[s[i]] = true;
                i++;
            }
        }
    }
    
bool isAnagrams(string s1, string s2) {
    string s3 = s1+s2;
    return (s3.find(s2));
}
string reverseString(string s) {
    int i = 0, j = s.size() - 1;
    while(i < j){
            char ch = s[j];
            s[j] = s[i];
            s[i] = ch;
            i++;
            j--;
        }
        return s;
    }
};
/* Implement strstr Returns the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.
https://leetcode.com/problems/implement-strstr/?tab=Description */
int strStr(string haystack, string needle) {
        int h = haystack.length();
        int n = needle.length();
        /* Base conditions */
        if (!n) return 0;
        if (n > h) return -1;
        /* Only compare h -n+1*/
        for (int i = 0;i< (h - n +1);i++) {
            int j =0;
            for (j =0;j<n;j++) {
                if (needle[j] != haystack[i+j]) break;
            }
            if (j == n) return i;
        }
        return -1;
}

string multiplyStrings(string num1, string num2) 
{
    int len1 = num1.length();
    int len2 = num2.length();
    string sum(len1+len2, '0');

    for(int i = len1-1; i >=0; i--) {
        int carry = 0;
        for(int j = len2-1; j >= 0; j--) {
            int tmp = (sum[i+j+1] - '0')
                    + (num1[i]-'0') * (num2[j]-'0')
                    + carry;
            sum[i+j+1] = (tmp % 10) + '0';
            carry = tmp/10;
        }
        sum[i] += carry;
    }

    size_t pos = sum.find_first_not_of('0');
    if(pos != string::npos) {
        return sum.substr(pos);
    }
    return "0";
}

void start_stests(int argc, char *argv[]) {
    S res;
    string s1 = "aabbcccdddeeffggggg";
    string s2 = "A man a plan a canal: Panama";
    string s4;
    string s5 = "ana";
    string s6 = "tan";
    string s7 = res.isAnagrams(s5,s6) ? " is anagram of ":" not anagram of ";
    cout << s5 << s7 << s6 << "\n";
    
    cout << s1 << "[Unique character index]"<< res.firstUniqChar(s1) <<"\n";
    for (int i = s1.size()-2; i < s1.size() ; i++) {
        s4.clear();
        s4.assign(s2,0,i);
        cout << s4 << "[Remove Duplicates]" ;
        res.removeDups(s4);
        cout << s4 <<"\n";
    }
    cout <<s2 <<" [reverse] " <<res.reverseString(s2) <<"\n";
    cout <<s1 <<" [ChangeString] "<< res.changeString(s1) <<"\n";
    
    string s3 = "45678900001";
    for (int i =s3.size() - 2; i<s3.size() ; i++) {
        s4.clear();
        s4.assign(s3 ,0,i);
        cout <<s4 <<" [converttoCurrency] "<< res.convertTocurrency(s4) <<"\n";
    }
    string s8= "pradeepgopanapalli";
    printf("Largestsubsequence(%s) ==> (%d) \n",s8.c_str(), res.findLargeSS(s8));
    
    
    string s9 ="123";
    string s10 = "200";
    printf("multiply(%s,%s) ==> (%s)\n",s9.c_str(), s10.c_str(), multiplyStrings(s9,s10).c_str());
}
