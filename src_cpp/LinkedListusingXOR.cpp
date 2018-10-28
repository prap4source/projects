#include <iostream> 
#include <stdio.h> 
#include <stdint.h>
#include "common.hpp"
using namespace std;
using namespace std;
typedef int EType;

    typedef struct Node {
        EType data;
        struct Node *xptr;
    } *Nodeptr;
class List {
  public:
    Nodeptr next;
    Nodeptr head;
    Nodeptr prev;
    Nodeptr curr;
    List();
    void InsertAtHead(EType element);
    void Traverse();
    //Nodeptr XOR(Nodeptr a , Nodeptr b);
};

List::List(){
    next = head = prev = curr = NULL;
}

struct Node * XOR(Nodeptr a, Nodeptr b) {
    return (struct Node *) ((uintptr_t)(a) ^ (uintptr_t)(b));
}

void List::InsertAtHead(EType element) {
    Nodeptr new_node = new Node;
    new_node->data = element;
    
    /* As new node is inserted before head pointers is XOR  of prev(NULL) & head */
    new_node->xptr = XOR(head, NULL);
    
    if (head != NULL){
        
        /* Find next node to head !!H!!->!!Next!!*/
        next = XOR(head->xptr, NULL);
        /* Now recalulate xptr in head */
        head->xptr = XOR(new_node, next);
    }
    printf("data %d next:%p \n",element, new_node->xptr);
    head = new_node;
}



void List::Traverse() {
    prev = NULL;
    curr = head;
    next = NULL;
    
    while (curr != NULL) {
        printf ("Node %d xptr %p\n", curr->data, curr);
        next = XOR(curr->xptr, prev);
        prev = curr;
        curr = next;
        
    }
}

void create_xlist(void) {
	List first;
	for (EType i =0; i <10; i ++) {
		first.InsertAtHead(i);
	}
	first.Traverse();
}
