#include <iostream>
#include <vector>
#include "common.hpp"
using namespace std;
/* Definition for singly-linked list. */
 struct ListNode {
   int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
  };
 
/* Definition for a binary tree node. */
  struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
  };
 
class Solution {
private:
    ListNode* findMid(ListNode* head, ListNode* tail) {
        ListNode *slow , *fast;
        slow = fast = head;
        while (fast != tail && fast->next != tail) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }
    TreeNode* sortedListToBST(ListNode* head, ListNode *tail) {
        if (head == tail) return NULL;
        /* Avoid one sort recursion if the node is last node */
        if (head->next == tail) {
            TreeNode *root = new TreeNode(head->val);
            return root;
        }
        ListNode* mid = findMid(head, tail);
        TreeNode *mTree = new TreeNode(mid->val);
        mTree->left = sortedListToBST(head, mid);
        mTree->right = sortedListToBST(mid->next, tail);

        return mTree;
    }
public:
    /* Convert sorted Linked list to balanced Binary search tree */
    TreeNode* sortedListToBST(ListNode* head) {
        return sortedListToBST(head, NULL);
    }
};
