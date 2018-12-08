#include <iostream>
#include <queue>
#include "common.hpp"
using namespace std;
typedef struct TreeNode {
    int val;
    struct TreeNode *left , *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
} *Treep;

class SingleTree {
    public:
        Treep root;
        SingleTree() { root = NULL; }
};
/* count nodes in complete balanaced tree */
int countNodes(TreeNode* root) {
        int lh =0 ,rh =0;
        if (root == NULL)
            return 0;
        TreeNode *l ,*r;
        l = r = root;
        while(l) {
            lh++;
            l =l->left;
        }
        while(r) {
            rh++;
            r = r->right;
        }
        if (lh == rh)
            return pow(2,lh)-1;
        return 1 + countNodes(root->left) + countNodes(root->right);
}
/* Validate if tree is bst or not,At node compare it with max and minimum, 
 * child nodes will get new max and min from parent 
 * based on left or right  */
int isValidBSTUtil(TreeNode *node, int min, int max) {
	if (node == NULL)
		return 0;
	if (node->val <= min || node->val >=max)
		return 1;
	/* Left nodes should be less than node->val and right nodes should be greater than node->val */
	return (isValidBSTUtil(node->left, min, node->val) && isValidBST(node->right,node->val,max));
}
bool isValidBST(TreeNode* root) {
	int min = INT_MIN, max = INT_MAX;
	return (isValidBSTUtil(root, min, max));
}

/* Build Balanced level tree from array */
void buildTreeLevelOrder(queue<Treep> &q, int arr[], int size) 
{
    int left = 1;
    for (int i = 1; i< size; i++)  {
        Treep newNode;
        Treep node = q.front();
        /* Element -1 means NULL node */
        newNode = (arr[i] == -1) ? NULL: (new TreeNode(arr[i]));
        /* If node is NULL then no left and right for that node right */
        if (left) {
            if (node) node->left = newNode;
            left = 0;
        } else  {
            if (node) node->right = newNode;
            q.pop();
            left = 1;
        }
        q.push(newNode);
    }
    cout <<"Built the tree \n";
}

void printTree(Treep root) {
    queue <Treep> q;
    q.push(root);
    while (1) {
        int nodes = q.size();
        if (nodes == 0) /* end of tree */
            break;
        while (nodes--) {
            Treep node = q.front();
            cout<<node->val<<" - ";
            q.pop();
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        cout<< "\n"; /*End of one Level */
    }
    
}
/* Invert nodes of tree 1,2,3 becomes 1,3,2 */
Treep invertTree(Treep root) {
    queue<Treep> q;
    q.push(root);
    
    while (q.size()) {
        Treep node = q.front();
        q.pop();
        if (node) {
            q.push(node->left);
            q.push(node->right);
            /* swap elements */ 
            Treep temp =node->left;
            node->left = node->right;
            node->right = temp;
        }
    }
    cout <<"After inverting tree \n";
    return root;
}
/* Determine if two trees are identical depth height */
bool isSameTree(TreeNode* p, TreeNode* q) {
        queue<Treep> p1, q1;
        p1.push(p);
        q1.push(q);
        while ((p1.size() && q1.size()) && (p1.size() == q1.size())) {
            Treep nodep = p1.front();
            Treep nodeq = q1.front();
            p1.pop();
            q1.pop();
            if (nodep && nodeq) {
              if (nodep->val != nodeq->val) 
                    return false;   
               p1.push(nodep->left);
               p1.push(nodep->right);
               q1.push(nodeq->left);
               q1.push(nodeq->right);
            } else if ((!nodep && nodeq) || (nodep && !nodeq)) {
                return false;
            }
        }
        if (p1.size() != q1.size()) 
            return false;    
        
        return true;
}
/* Find left most leaf node value */
int findLeft(TreeNode *node, int dir) {
        int l = 0  ,r = 0;
        if (node == NULL) return 0;
        if ((node->left == NULL) && (node->right == NULL)) {
                if (dir) return node->val;
                return 0;
        } 
        
        l = findLeft(node->left, 1);
        r = findLeft(node->right, 0);
        return l + r;
}

/* Build a balanced tree from sorted array */
TreeNode *sortedToBST(vector <int> &nums, int start, int end) {
        if (start > end)
            return NULL;
         int midx = start + (end - start) /2;
         TreeNode *temp = new TreeNode(nums[midx]);
         temp->left = sortedToBST(nums, start, midx-1);
         temp->right = sortedToBST(nums, midx+1, end);
         
         return temp;
}
TreeNode* sortedArrayToBST(vector<int>& nums) {
        cout <<"Array To BST \n";
        return sortedToBST(nums, 0, nums.size()-1);
}


/* Print tree from bottom up level i.e bottom nodes first */
vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> vec1;
        queue <Treep> q;
        if (root == NULL)
            return vec1;
        q.push(root);
        while (1) {
            int nodes = q.size();
            vector<int> vec;
            if (nodes == 0)
                break;
            while (nodes--) {
                Treep node = q.front();
                q.pop();
                if (node) {
                    vec.push_back(node->val);
                    if (node->left) q.push(node->left);
                    if (node->right) q.push(node->right);
                }
            }
            vec1.insert(vec1.begin(), vec);
        }
        return vec1;
}

/* Height of tree */
int height(Treep root) {
    int l_h, r_h ;
    if (root == NULL)
        return 0;
    l_h = height(root->left);
    r_h = height(root->right);
    return max(l_h , r_h) +1;
}
/* For this problem, a height-balanced binary tree is 
 defined as a binary tree in which the depth of the two
 subtrees of every node never differ by more than 1
 https://leetcode.com/problems/balanced-binary-tree/?tab=Description
 */
int isBalanced(TreeNode *root) {
        int l_h, r_h;
        if (root == NULL)
            return 0;
        l_h = isBalanced(root->left);
        if (l_h == -1) return -1;
        r_h = isBalanced(root->right);
        if (r_h == -1) return -1;
        if (abs(l_h-r_h) > 1)
            return -1;
        return max(l_h, r_h) + 1;
}
void clear_queue(queue<Treep> &q) {
    while (q.size()) q.pop();
}

void start_trees(int argc, char *argv[]) {
    SingleTree first;
    Treep root1,root2,root3;
    queue<Treep> q;
    int arr[] = {4,5,9,-1,-1,13,10,-1,-1,-1,-1,12,-1,18};
    int arr2[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,15,18,20,21};
    root1 = new TreeNode(arr[0]);
    q.push(root1);
    buildTreeLevelOrder(q, arr, sizeof(arr)/sizeof(arr[0]));
    printTree(root1);
    clear_queue(q);
    //root1 = invertTree(root1);
    root2 = new TreeNode(arr2[0]);
    q.push(root2);
    buildTreeLevelOrder(q, arr2, sizeof(arr2)/sizeof(arr2[0]));
    printTree(root2);
    cout <<height(root2) << " height of tree \n";
    cout <<isBalanced(root1) << " is balanced \n";
    cout <<"Compare two tree "<<isSameTree(root1, root2) <<" \n";
    vector <int> v1({1,2,3,5,6,7});
    root3 = sortedArrayToBST(v1);
    printTree(root3);
}
