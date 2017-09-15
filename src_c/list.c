
/*Linked list
  Insert element
  Linked list is already sorted */
#include "common.h"
 typedef struct slist {
 	  int data;
     struct slist *next;
} *pslist;

/* HEAD
  N1(3)->N2(6)->N3(10)
  HEAD
  N1(3)->N2(6)->N3(8)-N4(10)

  |3|->NULL 
  |6|->NULL
  insert(HEAD, 3)
  head->|3|->|6|->NULL

 pslist create(int key) {
  pslist curr;
  curr = malloc(sizeof(*curr));
  if (curr == NULL)
    return NULL;
  curr->data = key;
  curr->next = NULL;
  return curr;
}
*/
#if 0
pslist insert(pslist head, int key) {
    pslist tmp = head;
    pslist prev = NULL;
    pslist curr = create(key);  
   if (curr ==NULL)
      return NULL;
  if (head == NULL)
    return curr;
  while (tmp != NULL) {
    /* insert element before tmp*/
    if (tmp->data > key) {
			if (prev == NULL)	
      		head = curr; 
      else {
          prev->next = curr;
      }
      curr->next = tmp;
      break;
    }
    prev = tmp;
    tmp = tmp->next;
  }
  /* We need to insert at end of list */
  if (tmp == NULL)
    prev->next = curr;
  return head;
}
int verify(pslist head)
{
  pslist tmp = head;
  if (head == NULL)
    return 1;
  while (tmp->next != NULL) {
    if (tmp->data > tmp->next->data)
      	return 1;
    tmp = tmp->next;
  }
  return 0;
}

test() {
  
  
}

#endif



