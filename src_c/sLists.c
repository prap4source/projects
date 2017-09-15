/*
 * sLists.c
 * Copyright 2017 Pradeep Gopanapalli 
 * 
 */
#include "common.h"
#include "operations.h"
#ifndef MIN_NODES
#define MIN_NODES 0
#endif
#ifndef MAX_NODES
#define MAX_NODES 10200
#endif
#ifndef NODE_JUMP
#define NODE_JUMP 120
#endif
int num_nodes;
typedef struct slist {
    int data;
    struct slist *next;
} *pslist;

pslist create_node(int data) {
    pslist node = my_malloc(sizeof(*node));
    if (node == NULL)
        return NULL;
    num_nodes++;
    node->data = data;
    node->next = NULL;
    return node;
}
/* Insert element, Linked list is already sorted 
HEAD N1(3)->N2(6)->N3(10)
insert(HEAD, 8)
HEAD N1(3)->N2(6)->N3(8)-N4(10)
*/
int insert_node(pslist *head, int data) {
   pslist tmp =  *head;
   pslist prev = NULL;
   pslist newnode = create_node(data);
   
       
   if (newnode == NULL) {
	log_err("Unable to create node:%d", data);
	return EINVAL;
   }
   
   if (*head == NULL) {
       *head = newnode;
       return 0;
    }
   
   log("Creating node %d:%d",data, tmp->data);
   while (tmp != NULL) {
       if (data < tmp->data) {
	 if (prev == NULL)
	     *head = newnode;
	 else 
	    prev->next = newnode;
	 newnode->next = tmp;
	 break;
       }
       prev = tmp;
       tmp = tmp->next;
   }
   if (tmp == NULL) {
       prev->next = newnode;
   }
   return 0;
}

void print_nodes(pslist head) {
    pslist tmp = head;
    log_info("Printing Nodes total%d", num_nodes);
    while (tmp != NULL) {
	printf("%d :->",tmp->data);
	tmp = tmp->next;
    }
    printf("\n");
}


void delete_node(pslist *head, int data) {
    pslist tmp = *head;
    pslist prev = NULL; 
   	
    while (tmp != NULL) {
	if (tmp->data == data) {
	    if (prev == NULL) {
		*head = tmp->next;
	    } else {
		prev->next = tmp->next;
	    }
	    my_free(tmp);
	    break;
	}
	prev = tmp;
	tmp = tmp->next;
    }
    if(tmp == NULL)
	log_info("node%d not found head%p \n",data, *head);
    else
        num_nodes --;
}

void delete_all(pslist head) {
    pslist tmp = head;
    pslist next = NULL;
    while (tmp != NULL) {
	next = tmp->next;
	delete_node(&tmp, tmp->data);
	tmp = next;
    }
}

void verify_list(pslist head, int min, int max, int inc) {
    pslist tmp = head;
    
    for (int i = min; i< max; i += inc) {
	if (tmp == NULL) {
	    log_err("node:%d is not present ",i);
	    goto plist;
	} else if (tmp->data != i) {
	   log_err("mismatch(%d:%d)",i, tmp->data);
	   goto plist;   
	}
	tmp = tmp->next;
    }
    log_info("Verified list all nodes present ");
    return;
plist:
    for (int i = min; i<max; i += inc)
	printf("%d:-->",i);
    printf("\n");
}
    
void start_llist(int argc, char *argv[]) {
    pslist HEAD = NULL;
    int min = MIN_NODES;
    int jump = NODE_JUMP;
    int max = MAX_NODES;
    log_info("List properties: min%d max%d jump%d",min, max, jump); 
    for (int i = min; i < max; i+=jump) {
	if (insert_node(&HEAD, i) != SUCCESS) {
	    log_err("Unable to insert %d ",i);
	    break;
	}
    }
    
    //delete_node(&HEAD, 40);
    verify_list(HEAD, min, max, jump);
    print_nodes(HEAD);
    delete_all(HEAD);
}
