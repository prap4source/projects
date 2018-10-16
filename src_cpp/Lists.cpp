#include "common.hpp"
using namespace std;
typedef int EType;
typedef struct ListNode {
            EType data;
            struct ListNode *next;
            ListNode(int x) : data(x), next(NULL) {}
            ListNode() : next(NULL) {}
} *Nodeptr;
typedef ListNode Node;
class SingleList {
    private:
        Nodeptr temp;
     public:
        Nodeptr head;
        Nodeptr curr;
        SingleList() {
                head = temp = curr = NULL;
        }
	~SingleList() {
	    while (head != NULL) {
		temp = head->next;
		delete (head);
		head = temp;
	    }
	    head = temp = curr = NULL;
	}
        void PrintList();
/* Brute force method for Find pair for given sum in a sorted singly linked without extra space
  Assumptions no negative numbers , no repeated numbers 
  Link: http://www.geeksforgeeks.org/find-pair-given-sum-sorted-singly-linked-without-extra-space/
  */
void FindMatchingSum(EType sum) {
    temp = head;
    for (; temp != NULL; temp=temp->next) {
        if (temp->data > sum)
            continue;
        for (curr = temp->next; curr != NULL ; curr = curr->next) {
            if (temp->data + curr->data == sum) {
                cout<<"("<<temp->data<<","<<curr->data<<")"<<"\n";
                /* As there wont be any repeated numbers temp wont be involved
                in pair, We have to optimize to remove present curr from the next lookup */
                break;
            }
        }
    }
}
/* Find whether List has a cycle/loop or not and return the start of loop*/
ListNode* hasCycle(ListNode *head) {
        ListNode *fast, *slow;
	fast = slow = head;
	        
        while (fast && fast->next) {
            slow = slow->next;
	    fast = fast->next->next;
            if (fast == slow) { /* Cycle detected */
                /* detect start of the loop by following formula
                https://leetcode.com/problems/linked-list-cycle-ii/?tab=Solutions*/ 
		/* Once cycle is detected use one pointer start from the start node of list, 
		another pointer start from the first meeting node, all of them wake one step at a time, 
		the first time they meeting each other is the start of the cycle.*/
                slow = head;
                while (slow != fast) {
                    fast = fast->next;
                    slow = slow->next;
                }
                return fast;
            }
         }
        return NULL;
}
/* remove loop from list */
void removeTheLoop(ListNode *node)
{
    ListNode *fast, *slow, *prev;
    fast = slow = node;
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) /* Loop detected */
        {
            fast = node;
            prev = slow;
            while (fast != slow) {
                prev = slow;
                slow = slow->next;
                fast = fast->next;
            }
            prev->next = NULL;
            return;
        }
    }
}
/* Add node to end of List */
void Addnode(EType item) {
    Nodeptr one = new ListNode;
    one->next = NULL;
    one->data = item;
    
    temp = head;
    curr = head;
    
    while (curr != NULL) { 
        temp = curr;
        curr = curr->next;
    }
    /* No Nodes present */
    if (temp == NULL)
        head = one;
    else 
        temp->next = one;
}
/* Insert a element after "after" data */
void InsertAfter(EType after, EType data) {
    temp = head;
    while ( temp != NULL && temp->data != after)
        temp = temp->next;
        
    /* Element not found */
    if (temp == NULL) {
        cout <<"Element "<<after <<"Not found \n";
    } else  {
        Nodeptr newNode = new ListNode(0);
        newNode->data = data;
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

/* Insert a element before a given key */
void InsertBefore(EType before, EType data) {
    temp  = curr = head;
    
    while (curr != NULL && curr->data != before) {
        temp = curr ; /* temp points to previous node at end of loop */
        curr = curr->next;
    }
    
    if (curr == NULL) cout <<"Element "<<before <<"Not found \n";
    else {
        Nodeptr newNode = new ListNode(0);
        newNode->data = data;
        if (curr == head) { /* Node has to be added before head */
	    newNode->next = head;
	    head = newNode;
	} else {
            temp->next = newNode;
            newNode->next = curr;
        }
    }
}
/* Remove node */
void DeleteNode(EType item) {
    Nodeptr deleteNode = NULL;
    temp = head;
    curr = head;
    
    /*At EOL curr points to element(if found ) and temp to previous element*/
    while ((curr != NULL) && (curr->data != item)) {
        temp = curr;
        curr = curr->next;
    }
    
    if (curr == NULL) cout <<"Element not found"<<item <<"\n";
    else {
        deleteNode = curr;
        /* If node is head */
        if (deleteNode == head) {
            head = head->next;
        } else {
            temp->next = curr->next;
        }
        delete (deleteNode);
    }
}
}; /* End of Class */

/* Reverse linked List 
   Store next node in temp and traverse curr pointer to next element */
void reverseList(ListNode **head, bool print) {
    ListNode *result, *curr, *temp;
    curr = *head;
    temp = result = NULL;
    while (curr != NULL) {
        temp = curr->next;
        curr->next = result;
        result = curr;
        curr = temp;
    }
    *head = result;
    if (print)
        cout <<"After reveresing List \n";
}

ListNode *reverse(ListNode *head) {
    Node *curr = head;
    Node *temp, *result;
    temp = result = NULL;
    
    while (curr) {
        temp = curr->next;
        curr->next = result;
        result = curr;
        curr = temp;
    }
    
    return result;
}
/* reverse k-nodes in a linked list 
 https://leetcode.com/problems/reverse-nodes-in-k-group/#/description
 */
ListNode* reverseKGroup(ListNode* head, int k) {
        if (!head || !head->next)
            return head;
        int count = 0;
        ListNode *ref ,*curr, *result, *prev;
        ref = curr = head;
        prev = NULL;
        
        while (ref) {
            count ++;
            if (count >1 && (count == k)) {
                ref = ref->next;
                result = ref;
                /* Save present first node ,it will become last node 
                    after reverse */
                ListNode *save = curr, *temp;
                /* Reverse k nodes */
                while (count --) {
                    temp = curr->next;
                    curr->next = result;
                    result = curr;
                    curr = temp;
                }
                /* If this is first k-node reverse then update head */
                if (!prev)
                    head = result;
                else 
                    prev->next = result; /* Last node in previous iteration update now */
                prev = save; /*Last node in present iteration used for next update */
                curr = ref;
                count = 0;
            } else {
                ref =ref->next;
            }
        }
         printf("After reversing %d Node groups \n", k);
        return head;        
}

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
  Node *tf = reverse(l1);
  Node *ts = reverse(l2);
  Node dummy;
  Node *result = &dummy;
  int carry =0,sum=0;
  
  while (tf ||  ts || carry) {
      sum  = carry;
      if (tf) {
        sum += tf->data;
        tf = tf->next;
      }
       if (ts) {
        sum += ts->data;
        ts = ts->next;
       }
      result->next = new Node(sum % 10);
      carry = sum/10;
      result = result->next;
  }
  return (reverse(dummy.next));
}
/*check whether list is palindrome:  Reverse from middle of list and start comparing start and middle
Eg: 1,5,4,5,1
https://leetcode.com/problems/palindrome-linked-list/?tab=Description
*/
bool isPalindrome(ListNode* head) {
    ListNode *middle, *fast, *start, *end;
    bool is_bool = true;
    if (!head || !head->next)
        return is_bool;
    fast = middle = head;
    /* middle will point to middle of list */
    while (fast && fast->next) {
        middle = middle->next;
        fast = fast->next->next;
    }
    /* Reverse second half of list */
    reverseList(&middle, 0);
    start  = head;
    end = middle;
    /* Now start comparing start and reversed middle */
    while (end) {
        if (start->data != end->data) {
            is_bool = false;
            break;
        }
        end = end->next;
        start = start->next;
    }
    /* Now restore reversed middle and list will become 1,5,4,5,1 */
    reverseList(&middle, 0);
    string is = is_bool ? "yes" : "no";
    cout << is<< " List is  palindrome \n";
    return is_bool;   
}

/* Delete odd numbers in linked List */
void DeleteOdd(Nodeptr head) {
    Nodeptr prev,curr;
    Nodeptr temp = head;
    /* Start from even number */
    while (temp != NULL && ((temp->data % 2) != 0)) 
            temp = temp->next;
    
    if (temp == NULL)
        return;
    prev = temp;
    curr = temp->next;
    while (curr != NULL) {
        if ((curr->data % 2) != 0 ) {
            Nodeptr temp1 =  curr;
            prev->next = curr->next;
            delete (temp1);
            curr = prev->next;
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
    cout <<"Deleted Odd numbers\n";
 }

ListNode* deleteDuplicates(ListNode* head) {
        ListNode *temp , *curr;
        if (head == NULL)
            return NULL;
        temp = head;
        curr = head->next;
        while (curr) {
            if (curr->data == temp->data) {
                temp->next = curr->next;
                delete (curr);
                curr = temp->next;
            } else {
                temp = curr;
                curr = curr->next;
            }
        }
        cout <<"Deleted Duplicates numbers\n";
        return head;
    }
/* Delete all duplicate nodes including one which is duplicate */    
ListNode* deleteAllDuplicates(ListNode* head) {
        ListNode *first = head;
        ListNode *prev = NULL;
        int val;
        while (first && first->next) {
            if (first->next->data == first->data) {
                int val = first->data;
                while (first && (first->data == val)) {
                    ListNode *temp = first;
                    first = first->next;
                    delete (temp);
                }
                if (prev)
                    prev->next = first;
                else
                    head = first;
            } else {
                prev = first;
                first = first->next;
            }
        }
        cout <<"Delete All duplicate node including node  which is duplicate \n";
        return head;
    }

/* Print elements in List */
void SingleList::PrintList() {
    temp = head;
    cout <<"[";
    while (temp != NULL) {
        cout << temp->data <<",";
        temp = temp->next;
    }
    cout <<"]\n";
}

ListNode *mergeLists(ListNode* list1, ListNode* list2) {
        ListNode nhead;
        ListNode *newHead = &nhead;
        while (list1 && list2) {
            ListNode * &temp = (list1->data < list2->data)? list1:list2;
            newHead->next = temp;
            temp = temp->next;
            newHead = newHead->next;
        }
        /* If l1 or l2 is NULL */
        newHead->next = list1 ? list1: list2;
        return nhead.next;
}

/* Merge sorted KList's into one sorted List*/
ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode temp(INT_MIN);
        ListNode *newHead = &temp;
        int len,k;
        len = k = lists.size();
        if (!len) return (ListNode *)NULL;
        while (len > 1) {
             for (int i=0;i< (len /2);i++) {
                 
                  int end = len-i-1;
                  
                  /* Eliminate NULL Lists */
                  if (!lists[i] || !lists[end]) 
                        lists[i] = (lists[i] == NULL) ? lists[end] : lists[i];
                  else if (lists[i] && lists[end])
                        lists[i] = mergeLists(lists[i], lists[end]);
             }
             len = (len +1)/2;
        }
        cout <<"After Merging "<<k << "Lists \n";
        return lists[0];
}
/* Reverese nodes between m and n 
https://leetcode.com/problems/reverse-linked-list-ii/?tab=Description
Given 1->2->3->4->5->NULL, m = 2 and n = 4, return 1->4->3->2->5->NULL. */
ListNode* reverseBetween(ListNode* head, int m, int n) {
        ListNode new_head(0);
        new_head.next = head;
        ListNode *p = &new_head, *temp, *result;
        temp = result = NULL;
        for (int i = 1; i<m; i++) 
            p = p->next;
        ListNode *pre, *post;
        pre = p->next; /* store the start of reverse list node */
        post = p->next;
        /* reverse nodes m to n result will have reveresed nodes*/
        for (int i = 0; i<= (n -m ) ;  i++) {
            temp = post->next;
            post->next = result;
            result = post;
            post = temp;
        } 
        if (pre) pre->next = post; /* point mth node to nodes after n */
        p->next = result;
        cout <<"After reversing from "<<m<<" to "<< n<<"\n";
        return (new_head.next);
}

/* split the lists and merge the splits 
    This is top up approach with o(nlogn) Time comlexity and o(logn) space
    For bottom up approach 
    https://discuss.leetcode.com/topic/10382/bottom-to-up-not-recurring-with-o-1-space-complextity-and-o-nlgn-time-complextity*/
    ListNode* sortList(ListNode* head) {
        ListNode *fast, *slow;
        if (!head || !head->next)
            return head;
        slow = head, fast =head->next;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        ListNode *head2 = slow->next;
        slow->next = NULL;
        ListNode *head1 = head;
        return (mergeLists(sortList(head1), sortList(head2)));
}

/* group all odd nodes together followed by the even nodes. Please note here we are talking about the node number and not the value in the nodes.
   https://leetcode.com/problems/odd-even-linked-list/?tab=Description 
   Example: Given 1->2->3->4->5->NULL, return 1->3->5->2->4->NULL.
*/
ListNode* oddEvenList(ListNode* head) {
        ListNode o(INT_MIN), e(INT_MIN);
        ListNode *odd, *even;
        int i = 1;
        odd = &o;
        even = &e;
        while (head) {
            ListNode* &ref = ( (i++ % 2) ==0) ? even: odd;
            ref->next = head;
            head = head->next;
            ref = ref->next;
        }
        odd->next = e.next;
        even->next = NULL;
        
        cout <<"After Arranging Odd followed by even nodes "<<"\n";
        return (o.next);
}
ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *slow, *fast, *prev = NULL;
        slow = fast = head;
        while (fast != NULL) {
            fast = fast->next;
            if ((n != 1) && (fast !=NULL)) {
                n--;
                continue;
            }
            if (fast == NULL) {
                ListNode *temp = slow;
                if (prev == NULL) /*Head node to be deleted */
                   head = slow->next;
                else 
                   prev->next = slow->next;
                delete (temp);
            }
            prev = slow;
            slow = slow->next;
        }
        return head;
}
ListNode* mergeSameElements(ListNode *l1, ListNode *l2) {
    ListNode dummy;
    ListNode *newList = &dummy;
    
    while (l1 && l2) {
	if (l1->data == l2->data) {
	    newList->next = new ListNode(l1->data);
	    newList = newList->next;
	    l1 = l1->next;
	    l2 = l2->next;
	} else if (l1->data < l2->data) {
	    l1 = l1->next;
	} else {
	    l2 = l2->next;
	}
    }
    if (dummy.next) printf("After merging same elements in Lists \n");
    return (dummy.next);

}
void  toMath() {
    SingleList first,second,third,mList;
    EType arr1[] = {1,7,9};
    EType arr2[] = {2,5,6};
    EType arr3[] = {8,9,15};

    for (EType i = 0; i < (sizeof(arr1) / sizeof(arr1[0])) ; i ++)
	first.Addnode(arr1[i]);
    for (EType i = 0; i < (sizeof(arr2) / sizeof(arr2[0])) ; i ++)
	second.Addnode(arr2[i]);
    for (EType i = 0; i < (sizeof(arr3) / sizeof(arr3[0])) ; i ++) 
	third.Addnode(arr3[i]);

    cout <<"Initial List \n";
    first.PrintList();
    second.PrintList();
    third.PrintList();
    
    /* Palindrome */
    isPalindrome(first.head);
    
    /* Add Two numbers */
    mList.head = mergeSameElements(first.head, second.head);
    mList.PrintList();
    /* Add Two numbers */
    mList.head = addTwoNumbers(first.head, second.head);
    mList.PrintList();
   
}


void start_slist(int argc, char *argv[]) {
    SingleList first,second,third,mList;
    EType arr1[] = {1,7,9,11,14,15};
    EType arr2[] = {2,5,6,23,24,25};
    EType arr3[] = {8,9,15};

    for (EType i = 0; i < (sizeof(arr1) / sizeof(arr1[0])) ; i ++)
	first.Addnode(arr1[i]);
    for (EType i = 0; i < (sizeof(arr2) / sizeof(arr2[0])) ; i ++)
	second.Addnode(arr2[i]);
    for (EType i = 0; i < (sizeof(arr3) / sizeof(arr3[0])) ; i ++) 
	third.Addnode(arr3[i]);


    cout <<"Initial List \n";
    first.PrintList();
    second.PrintList();
    third.PrintList();
    
    //first.head = reverseBetween(first.head,1,2);
    //first.PrintList();
    first.head = oddEvenList(first.head);
    first.PrintList();
    first.head = deleteAllDuplicates(first.head);
    first.PrintList();
    DeleteOdd(first.head);
    first.PrintList();
    /* Merge Lists */
    vector<ListNode *> vec;
    vec.push_back(first.head);
    vec.push_back(second.head);
    vec.push_back(third.head);
#if 0
    mList.head = mergeKLists(vec);
    mList.PrintList();
    
    /*reverse k-node group elements */
    mList.head = reverseKGroup(mList.head, 3);
    mList.PrintList();
#endif

}
