#include <iostream> 
#include <stdio.h>
#include "common.hpp"

using namespace std;
typedef int EType ;
/* Define Class with double Linked List */
class DList {
  public:
  typedef struct Node {
      EType data;
      struct Node *next;
      struct Node *prev;
  } *Nodeptr;
  Nodeptr head;
  /* Temporary pointers */
  Nodeptr temp;
  Nodeptr curr;
  Nodeptr before;
  Nodeptr after;
  
  DList(); /*Constructor */
  ~DList(); /*Destructor */
  void AddatHead(EType element);
  void AddatEnd(EType element);
  void AddatNNode(EType element, EType N);
  void PrintList();
};
/* Initialize pointers */
DList::DList() {
    cout <<"Constructor called \n";
    head = temp = curr = before = after = NULL;
}
/* Add a node at start of the list and update head */
void DList::AddatHead(EType element) {
    Nodeptr newN = new Node();

    newN->data = element ;
    temp = head;
    if (temp != NULL) {
        newN->next = temp;
        temp->prev = newN;
    }
    
    head = newN;
}
/* Add a node at end of list */
void DList::AddatEnd(EType element) {
    Nodeptr newN = new Node();
    newN->data = element;
    
    temp = head;
    curr = NULL;
    
    while (temp != NULL) {
        curr = temp; /*this serves as previous node for next iteration */
        temp = temp->next;
    }
    
    if (curr != NULL) { /*This means  head is not NULL */
        curr->next = newN;
        newN->prev = curr;
    } else { /*head is NULL */
        head = newN;
    }
}

/* Add a new node at Nth node if N = 6 then element will be added at 6th node */
void DList::AddatNNode(EType element, EType N) {
    Nodeptr newN = new Node();
    EType i  = 1;
    curr = head;
    
    newN->data = element;
    while ((i < N) && (curr != NULL)) {
        i++;
        temp = curr; /*This will store previous element if there is N element */
        curr = curr->next;
    }
    
    if (curr == NULL) {
        cout <<"ELement not found at "<<N <<"\n";
        delete (newN);
    } else {
        temp->next = newN;
        newN->prev = temp;
        newN->next = curr;
        curr->prev = newN;
    }
}

void DList::PrintList() {
    temp = head ;
    for (;temp != NULL; temp = temp->next)  cout <<"ELement "<<temp->data <<"\n";
}

/* Delete each node in the list */
DList::~DList() {
    temp = head;
    cout <<"Destructor called \n";
    while (temp != NULL) {
        curr = temp->next;
        delete(temp);
        temp = curr;
    }
}

int  start_dlisttest(int argc, char *argv[]) {
 DList dllist;

for (int i = 1; i < 10 ; i++) 
    dllist.AddatEnd(i);

dllist.PrintList();
dllist.AddatNNode(30,5);
dllist.PrintList();

return 0;
}
