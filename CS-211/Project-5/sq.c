/**
* file:  sq.c
*
* description:  simple implementation of the 
*		service queue ADT as specified
*		in sq.h
*
*		Acts as a client of the linked list
*		ADT previously developed.
*/

#include <stdio.h>
#include <stdlib.h>
#include "sq.h"

typedef int ElemType;
#define FORMAT " %i "
#define DEFAULT 0

typedef struct node {
    ElemType val;
    struct node* prev;
    struct node* next;
} NODE;

typedef struct list_struct {
    int len;
    NODE *front;
    NODE *back;
} LIST;

struct service_queue {
    LIST* the_queue;
    LIST* buzzer_bucket;
    NODE* map[1000000];
};

/*
* returns pointer to newly created empty list
*/
LIST* lst_create() {
  LIST* l = malloc(sizeof(LIST));
  l->front = NULL;
  l->back = NULL;
  l->len = 0;
  return l;
}

void lst_free(LIST* l) {
  NODE *p = l->front;
  NODE *pnext;

  while(p != NULL) {
    pnext = p->next;   // keeps us from de-referencing a freed ptr
    free(p);
    p = pnext;
  }
  // now free the LIST 
  free(l);
}

void lst_print(LIST* l) {
NODE *p = l->front;

  printf("[");
  if (l->len != 0) {
    while(p != NULL) {
      printf(FORMAT, p->val);
      p = p->next;
    }
  } else {
    printf(" ");
  }
  printf("]\n");
}

int lst_length(LIST* l) {
  return l->len;
}

int lst_is_empty(LIST* l) {
  return l->front == NULL;
}

NODE* lst_push_front(LIST* l, ElemType val) {
  NODE* p = malloc(sizeof(NODE));
  p->val = val;
  p->prev = NULL;
  p->next = l->front;
  if (l->front)
    l->front->prev = p;
  l->front = p;
  if(!l->back)   // was empty, now one elem
      l->back = p;
  l->len++;
  return p;
}

NODE* lst_push_back(LIST* l, ElemType val) {
  if(!l->back)   // list empty - same as push_front
    return lst_push_front(l, val);
  else {  // at least one element before push
    NODE* p = malloc(sizeof(NODE));
    p->val = val;
    p->prev = l->back;
    p->next = NULL;
    l->back->next = p;
    l->back = p;  
    l->len++;
    return p;
  }
}

ElemType lst_pop_front(LIST* l) {
  if (lst_is_empty(l)) { // If list is empty...
    return DEFAULT;
  } else {
    // Use a temp pointer
    NODE* temp = l->front;
    ElemType val = l->front->val;

    // Reassign pointers
    l->front = l->front->next;
    if (l->front)
      l->front->prev = NULL;

    // Free node
    free(temp);
    l->len--;

    // If list is empty...
    if (l->len == 0) {
      l->front = NULL;
      l->back = NULL;
    }
    return val;
  }
}

/*
*    if list is empty, we do nothing and return arbitrary value
*    otherwise, the last element in the list is removed and its
*      value is returned.
*/
ElemType lst_pop_back(LIST* l) {
  if (lst_is_empty(l)) { // If list is empty...
    return DEFAULT;
  } else {
    // Use a temp pointer
    NODE* temp = l->back;
    ElemType val = l->back->val;

    // Reassign pointers
    l->back = l->back->prev;
    if (l->back)
      l->back->next = NULL;

    // Free node
    free(temp);
    l->len--;

    // If list is empty...
    if (l->len == 0) {
      l->front = NULL;
      l->back = NULL;
    }
    return val;
  }
} 

int lst_remove(LIST* l, NODE* n) {
  NODE* p;
  NODE* tmp;

  if(!l->front || !n) return 0;
  if(l->front == n) {
	  lst_pop_front(l);
	  return 1;
  }
  if (l->back == n) {
    lst_pop_back(l);
    return 1;
  }
  // lst non-empty; no match on 1st or last elem
  p = l->front;
  n->prev->next = n->next;
  n->next->prev = n->prev;
  free(n);
  l->len--;
  return 1;
}

/**
* Function: sq_create()
* Description: creates and intializes an empty service queue.
* 	It is returned as an SQ pointer.
*/
SQ * sq_create() {
  SQ* q;

  q = malloc(sizeof(SQ));

  q->the_queue = lst_create();
  q->buzzer_bucket = lst_create();
  for (int i = 0; i < 1000000; i++) {
    q->map[i] = NULL;
  }

  return q;
}

/**
* Function: sq_free()
* Description:  see sq.h
*
* RUNTIME REQUIREMENT:  O(N_t)  where N_t is the number of buzzer 
*	IDs that have been used during the lifetime of the
*	service queue; in general, at any particular instant
*	the actual queue length may be less than N_t.
*
*	[See discussion of in header file]
*
* RUNTIME ACHIEVED:  O(N)
*
*/
void sq_free(SQ *q) {

  lst_free(q->the_queue);
  lst_free(q->buzzer_bucket);

  free(q);
}

/**
* Function: sq_display()
* Description:  see sq.h
*
* REQUIRED RUNTIME:  O(N)  (N is the current queue length).
* ACHIEVED RUNTIME:  O(N)  YAY!!
*/
void sq_display(SQ *q) {

  printf("current-queue contents:\n    ");
  lst_print(q->the_queue);
  printf("\n");
}

/**
* Function: sq_length()
* Description:  see sq.h
*
* REQUIRED RUNTIME:  O(1)
* ACHIEVED RUNTIME:  O(1)
*/
int  sq_length(SQ *q) {
  return lst_length(q->the_queue);
}

/**
* Function: sq_give_buzzer()
* Description:  see sq.h
*
* REQUIRED RUNTIME:  O(1)  ON AVERAGE or "AMORTIZED":  in other words, if 
*		there have been M calls to sq_give_buzzer, the total
*		time taken for those M calls is O(M).
*
*		An individual call may therefore not be O(1) so long
*		as when taken as a whole they average constant time.
*
*		(Hopefully this reminds you of an idea we employed in
*		the array-based implementation of the stack ADT).
*
* ACHIEVED RUNTIME: O(1)
*/
int  sq_give_buzzer(SQ *q) {
  int buzzer;

  if(!lst_is_empty(q->buzzer_bucket)) {
    buzzer = lst_pop_front(q->buzzer_bucket);
  }
  else {
    /*  invariant:  
        if no re-useable buzzers, the buzzers 
        in the queue are {0,1,2,...,N-1} where
        N is the queue length.

        Thus, the smallest available new buzzer 
        is N
        */
    buzzer = sq_length(q);
  }
  q->map[buzzer] = lst_push_back(q->the_queue, buzzer);
  return buzzer;
}

/**
* function: sq_seat()
* description:  see sq.h
*
* REQUIRED RUNTIME:  O(1)
* ACHIEVED RUNTIME:  O(1)
*/
int sq_seat(SQ *q) {
int buzzer;

	if(lst_is_empty(q->the_queue))
	  return -1;
	else{
	  buzzer = lst_pop_front(q->the_queue);
	  lst_push_front(q->buzzer_bucket, buzzer);
    q->map[buzzer] = NULL;
	  return buzzer;
	}
} 



/**
* function: sq_kick_out()
*
* description:  see sq.h
*
* REQUIRED RUNTIME:  O(1)
* ACHIEVED RUNTIME:  ???
*/
int sq_kick_out(SQ *q, int buzzer) {
  if(lst_remove(q->the_queue, q->map[buzzer])) {
    lst_push_front(q->buzzer_bucket, buzzer);
    q->map[buzzer] = NULL;
    return 1;
  }
  else
    return 0;
}

/**
* function:  sq_take_bribe()
* description:  see sq.h
*
* REQUIRED RUNTIME:  O(1)
* ACHIEVED RUNTIME:  ???
*/
int sq_take_bribe(SQ *q, int buzzer) {

  /* remove buzzer then push it on front */
  if(lst_remove(q->the_queue, q->map[buzzer])) {
    q->map[buzzer] = lst_push_front(q->the_queue, buzzer);
    return 1;
  }
  else {
    /* person has to be in line to offer a bribe */
    return 0;
  }
}