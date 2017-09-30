#include <iostream> 
#include <queue>
#include "common.hpp"
using namespace std;
typedef int EType;
typedef struct tree {
            EType element;
            struct tree *left;
            struct tree *right;
            tree(int key) : element(key), left(NULL), right(NULL) {}
}*Treeptr;
class BTree {
    public:
        Treeptr root;
        BTree(): root(NULL) {};
        void AddElement(EType key);
        void PrintTreeInOrder();
        void PrintChildren(EType key);
        Treeptr FindNodePtrP(EType key);
    private:
        void CreateElementP(EType key, Treeptr ptr);
        void PrintTreeInOrderP(Treeptr ptr);
        Treeptr FindNodePtrP(EType key, Treeptr ptr);
};

void BTree::PrintChildren(EType key) {
    Treeptr node = FindNodePtrP(key, root);
    
    if (node != NULL) {
        cout << "\n" << "Parent "<<node->element <<"\n";
        node->left  == NULL ? cout <<"Left NULL" <<"\n" : cout <<"Left Child "<<node->left->element <<"\n";
        node->right  == NULL ? cout <<"Right NULL" <<"\n" : cout <<"Right Child "<<node->right->element <<"\n";
    } else cout <<"Node is NULL" <<"\n";
}
/* Find key and return pointer address of it */
Treeptr BTree::FindNodePtrP(EType key, Treeptr ptr) {
    if (ptr != NULL) {
        if (key < ptr->element) FindNodePtrP(key, ptr->left);
        else if (key > ptr->element) FindNodePtrP(key, ptr->right);
        else return ptr;
    } else {
        cout << "\n" << key<<" Not Found \n";
    }
    return NULL;
}

Treeptr BTree::FindNodePtrP(EType key) {
    queue<Treeptr> q;
    q.push(root);
    while (1) {
        Treeptr node = q.front();
        q.pop();
        if (node == NULL) 
            return NULL;
        if (key == node->element) {
            cout <<"Found node "<<node->element<<"\n";
            return node;
        } else if (key < node->element) {
            q.push(node->left);
        } else 
            q.push (node->right);
    }
    return NULL;
}

void BTree::AddElement(EType key) {
    /* This is the first node */
    if (root == NULL) root = new tree(key);
    else CreateElementP(key, root);
}


void BTree::CreateElementP(EType key, Treeptr ptr) {
    if (key < ptr->element) { /*Add element to left */
        if (ptr->left != NULL) CreateElementP(key, ptr->left);
        else ptr->left = new tree(key);
    } else if (key > ptr->element) { /*Add element to right */
        if (ptr->right != NULL) CreateElementP(key, ptr->right);
        else ptr->right = new tree(key);
    } else cout <<"Element "<<key <<"already added \n";
}

void BTree::PrintTreeInOrder() {
    PrintTreeInOrderP(root);
}
/* In inorder traversal , 1-> Traverse left 2->Print node 3-> Traverse right */
void BTree::PrintTreeInOrderP(Treeptr ptr) {
    if (root != NULL) {
        if (ptr->left != NULL)  PrintTreeInOrderP(ptr->left);
        /*Print node */
        cout << ptr->element<<"  ";
        if (ptr->right != NULL) PrintTreeInOrderP(ptr->right);
    } else cout <<"Tree is empty \n";
}
void start_btree(int argc, char *argv[]) {
    int a[] = {4,3,1,2,9,10,14,12};
    BTree t;

    for (int i=0; i < sizeof(a)/sizeof(a[0]);i++)
	t.AddElement(a[i]);

    t.PrintTreeInOrder();
    for (int i=0; i < sizeof(a)/sizeof(a[0]);i++)
	t.PrintChildren(a[i]);
    t.FindNodePtrP(a[5]);
}

