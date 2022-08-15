#include <stdio.h>
#include <stdlib.h>
#include "deq.h"

/**
* See deq.h for expected behavior of functions
**/

typedef struct dnode {
    ElemType val;
    struct dnode *next;
    struct dnode *prev;
} DNODE;


struct deq_struct {
    DNODE *front;
    DNODE *back;
};


/*
* returns pointer to newly created empty list
*/
DEQ *deq_create() {
DEQ *q = malloc(sizeof(DEQ));

  q->front = NULL;
  q->back = NULL;
  return q;
}

void deq_free(DEQ *q) {
DNODE *p = q->front;
DNODE *pnext;

  while(p != NULL) {
    pnext = p->next;   // keeps us from de-referencing a freed ptr
    free(p);
    p = pnext;
  }
  // now free the DEQ 
  free(q);
}

void deq_print(DEQ *q) {
DNODE *p = q->front;

  printf("[");
  while(p != NULL) {
    printf(FORMAT, p->val);
    p = p->next;
  }
  printf("]\n");
}


// DONE: non-recursive print-reverse
void deq_print_rev(DEQ *q) {
  DNODE* p = q->back;
  
  printf("[");
  while (p) {
    printf(FORMAT, p->val);
    p = p->prev;
  }
  printf("]\n");
}

void deq_push_front(DEQ *l, ElemType val) {
DNODE *p = malloc(sizeof(DNODE));

  p->val = val;
  p->next = l->front;
  p->prev = NULL;
  
  l->front = p;
  if(l->back == NULL)   // was empty, now one elem
      l->back = p;
  else{
    p->next->prev = p;
  }
}

/* DONE */
void deq_push_back(DEQ *l, ElemType val) {
  DNODE* p = malloc(sizeof(DNODE));
  
  p->val = val;
  p->next = NULL;
  p->prev = l->back;

  l->back = p;
  if (!l->front) {
    l->front = p;
  } else {
    p->prev->next = p;
  }
}

/* DONE */
int deq_pop_front(DEQ *l, ElemType *val) {
  if (l->front) {
    DNODE* r = l->front;
    *val = r->val;
    l->front = r->next;
    l->front->prev = NULL;
    free(r);
    return 1;
  }
  return 0;
}

/* DONE */
int deq_pop_back(DEQ *q, ElemType *val) {
  if (q->back) {
    DNODE* r = q->back;
    *val = r->val;
    q->back = r->prev;
    q->back->next = NULL;
    free(r);
    return 1;
  }
  return 0;
} 


int deq_is_empty(DEQ *q) {
  return q->front == NULL;
}




/* These are "sanity checker" functions that check to see
*     list invariants hold or not.
*/
int deq_sanity1(DEQ *q) {
  if(q->front == NULL && q->back != NULL){
    fprintf(stderr, "lst_sanity1 error:  front NULL but back non-NULL\n");
    return 0;
  }
  if(q->back == NULL && q->front != NULL){
    fprintf(stderr, "lst_sanity1 error:  back NULL but front non-NULL\n");
    return 0;
  }
  return 1;
}

int deq_sanity2(DEQ *q) {
  if(q->back != NULL && q->back->next != NULL) {
    fprintf(stderr, "lst_sanity2 error:  back elem has a non-NULL next?\n");
    return 0;
  }
  return 1;
}
int deq_sanity3(DEQ *q) {
  if(q->front!= NULL && q->front->prev != NULL) {
    fprintf(stderr, "lst_sanity3 error:  front elem has a non-NULL prev?\n");
    return 0;
  }
  return 1;
}


/*
* function:  find_back()
* description:  returns a pointer to the last
*               node of the given list.
*		Note that we are operating at
*		the "node level".
*
*		if p is NULL, NULL is returned.
*
* purpose:  mostly for debugging -- enables sanity3
*/
static DNODE * find_back(DNODE *p) {

  if(p ==  NULL)
    return NULL;

  while(p->next != NULL) {
    p = p->next;
  }
  return p;
}

/*
*   makes sure that the back pointer is also the last reachable
*    node when you start walking from front.
*    HINT:  use pointer comparison
*/
int deq_sanity4(DEQ *q) {
DNODE *real_back;

  real_back = find_back(q->front);

  return (real_back == q->back);
}










