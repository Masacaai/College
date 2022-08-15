/**
 * @file llist.c
 * @author Mohammed Aaqel Shaik Abdul Mazeed (mshai4@uic.edu)
 * @brief Linked list implementation
 */

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/**
* See list.h for expected behavior of functions
**/

typedef struct node {
    ElemType val;
    struct node *next;
} NODE;


struct list_struct {
    int len;
    NODE *front;
    NODE *back;
};


/*
* returns pointer to newly created empty list
*/
LIST *lst_create() {
LIST *l = malloc(sizeof(LIST));

  l->front = NULL;
  l->back = NULL;
  l->len = 0;
  return l;
}

void lst_free(LIST *l) {
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

void lst_print(LIST *l) {
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


/**
*   function:  lst_are_equal
*   description:  returns true(1) if lst1 and lst2
*      contain exactly the same sequenc of values.
*      Returns 0 otherwise.
**/
int lst_are_equal(LIST *lst1, LIST *lst2) {
  if (lst1->len != lst2->len) {
    return 0;
  }
  // Declare two pointers for traversal
  NODE* cur1 = lst1->front;
  NODE* cur2 = lst2->front;
  while (cur1 && cur2) {
    // If current values differ...
    if (cur1->val != cur2->val) {
      return 0;
    }
    cur1 = cur1->next;
    cur2 = cur2->next;
  }
  // If no differring values are found, return 1.
  return 1;
}

/**
 *  Recursive helper function for lst_print_rev
 */
void _revPrint(NODE* cur) {
  // If next pointer is not NULL...
  if (cur->next) {
    _revPrint(cur->next);
    printf(", %i", cur->val);
  }
}

/**
* print in reverse order 
*
* Try to do without looking at notes!
* Hints:  recursive helper function
*/
void lst_print_rev(LIST *l) {
  printf("[");
  // If list isn't empty...
  if (l->back) {
    printf("%i", l->back->val);
    _revPrint(l->front);
  } else { // If list IS empty...
    printf(" ");
  }
  printf("]\n");
}

void lst_push_front(LIST *l, ElemType val) {
NODE *p = malloc(sizeof(NODE));

  p->val = val;
  p->next = l->front;
  
  l->front = p;
  if(l->back == NULL)   // was empty, now one elem
      l->back = p;
  l->len++;
}

void lst_push_back(LIST *l, ElemType val) {
  NODE *p;

  if(l->back == NULL)   // list empty - same as push_front
    lst_push_front(l, val);
  else {  // at least one element before push
    p = malloc(sizeof(NODE));
    p->val = val;
    p->next = NULL;
    l->back->next = p;

    l->back = p;  
    l->len++;
  }
}

/** 
*   modifications to enable this operation
*   to execute in O(1) time.  (You will almost
*   certainly modify other functions and the 
*   data structure itself -- see header).
**/
int lst_length(LIST *l) {
  return l->len;
}

int lst_is_empty(LIST *l) {
  return l->front == NULL;
}

/** 
 *    function:  lst_count
*     description:  Counts number of occurrences 
*     		of x in the list and returns 
*     		that value.
*/
int lst_count(LIST *l, ElemType x) {
  int num = 0;
  NODE* cur = l->front;
  while (cur) {
    if (cur->val == x) {
      num++;
    }
    cur = cur->next;
  }
  return num;
}

/* These are "sanity checker" functions that check to see
*     list invariants hold or not.
*/
int lst_sanity1(LIST *l) {
  if(l->front == NULL && l->back != NULL){
	fprintf(stderr, "lst_sanity1 error:  front NULL but back non-NULL\n");
	return 0;
  }
  if(l->back == NULL && l->front != NULL){
	fprintf(stderr, "lst_sanity1 error:  back NULL but front non-NULL\n");
	return 0;
  }
  return 1;
}

int lst_sanity2(LIST *l) {
  if(l->back != NULL && l->back->next != NULL) {
	fprintf(stderr, "lst_sanity2 error:  back elem has a non-NULL next?\n");
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
static NODE * find_back(NODE *p) {

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
int lst_sanity3(LIST *l) {
NODE *real_back;

  real_back = find_back(l->front);

  return (real_back == l->back);
}

ElemType lst_pop_front(LIST *l) {
ElemType ret;
NODE *p;
 

  if(lst_is_empty(l))
	return DEFAULT;   // no-op

  ret = l->front->val;
  
  if(l->front == l->back) {  // one element
	free(l->front);
	l->front = NULL;
	l->back = NULL;
  }
  else {
	p = l->front;  // don't lose node being deleted
	l->front = l->front->next;  // hop over
	free(p);
  }
  return ret;
}

/*
*    if list is empty, we do nothing and return arbitrary value
*    otherwise, the last element in the list is removed and its
*      value is returned.
*/
ElemType lst_pop_back(LIST *l) {
  if (l->len == 0) { // If list is empty...
    return DEFAULT;
  } else {
    // Use a temp pointer
    NODE* temp = l->back;
    ElemType val = l->back->val;

    // Find second-to-last node
    NODE* cur = l->front;
    while (cur->next && cur->next->next) {
      cur = cur->next;
    }
    l->back = cur;
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

/**
 * Recursive helper function for lst_reverse 
 */
void _reverse(NODE* cur) {
  // If the next pointer of the
  // next node points to NULL;
  if (!cur->next->next) {
    cur->next->next = cur;
  } else {
    _reverse(cur->next);
    cur->next->next = cur;
  }
}

/* 
*  For full credit, you cannot allocate any new memory!
*
*  description:  self-evident 
*/
void lst_reverse(LIST *l) {
  // Switch front and back pointers
  NODE* temp = l->front;
  l->front = l->back;
  l->back = temp;
  // If list has more than one node...
  if (l->len > 1) {
    _reverse(l->back);
    l->back->next = NULL;
  }
}


/*
* removes first occurrence of x (if any).  Returns
*   0 or 1 depending on whether x was found
*/
int lst_remove_first(LIST *l, ElemType x) {
NODE *p;
NODE *tmp;

  if(l->front == NULL) return 0;
  if(l->front->val == x) {
	lst_pop_front(l);
	return 1;
  }
  // lst non-empty; no match on 1st elem
  p = l->front;

  while(p->next != NULL) {
     if(x == p->next->val) {
	tmp = p->next;
	p->next = tmp->next;
	if(tmp == l->back) 
	    l->back = p;
	free(tmp);
	return 1;
     }
     p = p->next;
  }
  return 0;
}


/**
* function: lst_remove_all_slow
* description:  removes all occurrences of x
*   from given list (if any).
*   Returns number of occurrences (i.e., deletions).
* 
* notes:  it is called "slow" because in the worst
*   case, it takes quadratic time.
*   (Discussion of why and when this happens is a
*   lecture topic).
*/
int lst_remove_all_slow(LIST *l, ElemType x) {
  int n=0;
  while(lst_remove_first(l, x))
    n++;
  return n;
}

/** 
 * function: lst_sra_bad_case (sra:  slow_remove_all)
 *
 * description: constructs a list of length n such that 
 * the above function takes quadratic time to remove
 * all occurrences of a specified value. 
 *
 * By convention, the specified value will be 0
 */
LIST *lst_sra_bad_case(int n) {
  LIST *l = lst_create();
  int i;
  int k=n/2;

  for(i=0; i<k; i++) {
    lst_push_front(l, 0);
  }
  for(i=0; i<n-k; i++) {
    lst_push_front(l, 1);
  }
  return l;
}

/** 
*   function:  lst_remove_all_fast
*   description:  same behavior/semantics as
*      lst_remove_all_slow.  However, this function
*      must guarantee linear time worst case 
*      runtime (hence, "fast").
*
*   REQUIREMENT:  linear worst-case runtime.
*
*   Note:  your solution may be either recursive or 
*   iteratieve.
**/
int lst_remove_all_fast(LIST *l, ElemType x) {
  int num = 0;
  NODE* cur = l->front;
  NODE* prev = NULL;
  while (cur) {
    if (cur->val == x) {
      NODE* temp = cur;
      // If prev exists (If this isn't the first node)...
      if (prev) {
        prev->next = cur->next;
      } else {
        l->front = cur->next;
      }
      // Advance pointer to next node
      cur = cur->next;
      free(temp);
      l->len--;
      num++;
    } else {
        prev = cur;
        cur = cur->next;
    }
  }
  return num;
}

int lst_is_sorted(LIST *l){
NODE *p = l->front;

  while(p!=NULL && p->next != NULL) {
	if(p->val > p->next->val)
	  return 0;
	p = p->next;
  }
  return 1;
}



/** 
* function:  lst_insert_sorted
*
* description:  assumes given list is already in sorted order
*	   and inserts x into the appropriate position
* 	   retaining sorted-ness.
* Note 1:  duplicates are allowed.
*
* Note 2:  if given list not sorted, behavior is undefined/implementation
* 		dependent.  We blame the caller.
* 		So... you don't need to check ahead of time if it is sorted.
*/
void lst_insert_sorted(LIST *l, ElemType x) {
  NODE* n = malloc(sizeof(NODE));
  n->val = x;
  // Case 1: List is empty
  if (l->len == 0) {
    n->next = NULL;
    l->front = n;
    l->back = n;
  // Case 2: Value is inserted at beginning
  } else if (x < l->front->val) {
    n->next = l->front;
    l->front = n;
  // Case 3: Value is inserted at end
  } else if (x > l->back->val) {
    n->next = NULL;
    l->back->next = n;
    l->back = n;
  // Case 4: Value is inserted in the middle
  } else {
    NODE* cur = l->front;
    NODE* prev = NULL;
    while (cur->val < x) {
      prev = cur;
      cur = cur->next;
    }
    n->next = cur;
    prev->next = n;
  }
  l->len++;
}

/**
 * function:  lst_merge_sorted
 *
 * description:  assumes both list a and b are in
 * 	sorted (non-descending) order and merges them
 * 	into a single sorted list with the same
 * 	elements.  
 *
 * 	This single sorted list is stored in a while
 * 	b becomes empty.
 *
 * 	if either of given lists are not sorted, 
 * 	we blame the caller and the behavior is
 * 	implementation dependent -- i.e., don't worry
 * 	about it!
 *
 * 	Example:
 *
 * 		a:  [2 3 4 9 10 30]
 * 		b:  [5 8 8 11 20 40]
 *
 * 		after call on (a,b)
 *
 * 		a:  [2 3 4 5 8 8 9 10 11 20 30 40]
 * 		b:  []
 * 
 * implementation:  should not allocate ANY new list
 * 	nodes -- it should just re-link existing
 * 	nodes.
 *
 * 	Must be linear time in the |a|+|b| -- i.e.,
 * 	the total number of elements being processed.
 */
void lst_merge_sorted(LIST *a, LIST *b){
  // If a is empty, just reassign pointers
  if (!a->front) {
    a->front = b->front;
    a->back = b->back;
    a->len = b->len;
  } else {
    NODE* curA = a->front;
    NODE* prevA = NULL;
    NODE* curB = b->front;
    while (curB) {
      NODE* nextB = curB->next;
      // If node is inserted at beginning
      if (curB->val < a->front->val) {
        curB->next = a->front;
        a->front = curB;
      // If node is inserted at end
      } else if (curB->val > a->back->val) {
        curB->next = NULL;
        a->back->next = curB;
        a->back = curB;
      // If node is inserted in the middle
      } else {
        while (curA->val < curB->val) {
          prevA = curA;
          curA = curA->next;
        }
        curB->next = curA;
        prevA->next = curB;
      }
      curB = nextB;
    }
    // Adjust length of a
    a->len += b->len;
  }
  // Set b to be empty
  b->front = NULL;
  b->back = NULL;
  b->len = 0; 
}

/**
 *  Recursive helper function for lst_clone
 */
NODE* _clone(NODE* a) {
  if (!a) {
    return NULL;
  }
  NODE* b = malloc(sizeof(NODE));
  b->val = a->val;
  b->next = _clone(a->next);
  return b;
}

/**
* function:  lst_clone
*
* description:  makes a "deep copy" of the given list a
*   and returns it (as a LIST pointer).
*
*/
LIST * lst_clone(LIST *a) {
  LIST* b = lst_create();
  b->front = _clone(a->front);
  b->back = find_back(b->front);
  b->len = a->len;
  return b;
}

/**
* function:  lst_from_array 
*
* description:  creates a new list populated with the
*      elements of array a[] in the same order as 
*      they appear in a[] (element at a[0] will be the
*      first element in the list and so-on).  List is
*      returned as a LIST pointer.
*
*      Parameter n indicates the length of the given array.
*
* runtime requirement:  THETA(n)
*/
LIST * lst_from_array(ElemType a[], int n){
  LIST* l = lst_create();
  l->len = n;
  // Create front node
  l->front = malloc(sizeof(NODE));
  l->front->val = a[0];
  NODE* prev = l->front;
  // Go through array, creating and linking nodes
  for (int i = 1; i < n; ++i) {
    NODE* cur = malloc(sizeof(NODE));
    cur->val = a[i];
    prev->next = cur;
    prev = cur;
  }
  // Assign back pointer and set next to NULL
  l->back = prev;
  l->back->next = NULL;
  return l;
}


/**
* function:  lst_to_array 
*
* description:  allocates an array of ElemType and populates
*         it with the elements in the given list (as with
*         lst_from_array elements are in the same order in
*         both data structures).
*
* runtime requirement:  THETA(n)
*
*/
ElemType * lst_to_array(LIST *lst) {
  ElemType* a = malloc(lst->len * sizeof(int));
  NODE* cur = lst->front;
  int i = 0;
  while (cur) {
    a[i++] = cur->val;
    cur = cur->next;
  }
  return a;
}


/**
* TODO
* function:  lst_prefix
*
* description:  removes the first k elements from the
*               given list which are used to form a new list
*		which is then returned.
*
*		if n is the length of the given list, we have the
*		following boundary conditions:
*
*		  if k==0:
*			lst unchanged and an empty list returned
*		  if k>=n:
*			lst becomes empty and a list containing
*			all elements previously in lst is returned.
*
*		examples:
*
*		  EX1:  lst:  [2, 3, 9, 7, 8]
*			k:    3
*
*			after call:
*			   lst:  [7, 8]
*			   returned list:  [2, 3, 9]
*
*		  EX2  lst:  [2, 3, 9, 7, 8]
*			k:    0
*
*			after call:
*			   lst:  [2, 3, 9, 7, 8]  (unchanged)
*			   returned list:  []
*
*		  EX3  lst:  [2, 3, 9, 7, 8]
*			k:    5
*
*			after call:
*			   lst:  []
*			   returned list:  [2, 3, 9, 7, 8]
*
* REQUIREMENTS:
*
*	RUNTIME:  THETA(n) worst case where n is the length of the given list
*
*       ORDERING:  the ordering of the returned prefix should be the same as
*                  in the given list
*
*       MEMORY:    for full credit, no new nodes should be allocated or deallocated;
*		   you should just "re-use" the existing nodes.  HOWEVER, you will
*		   need to allocate a LIST structure itself (i.e., for the returned
*		   list).
*/
LIST * lst_prefix(LIST *lst, unsigned int k) {
  LIST* l = lst_create();
  // Ensure k != 0. if k == 0, we do nothing.
  if (k != 0) {
    // If k < length of list...
    if (k < lst->len) {
      l->len = k;
      lst->len -= k;
      l->front = lst->front;
      NODE* cur = lst->front;
      NODE* prev = NULL;
      // Find node where prefix ends
      for (int i = 0; i < k; ++i) {
        prev = cur;
        cur = cur->next;
      }
      // Reassign corresponding front and back pointers
      lst->front = cur;
      l->back = prev;
      l->back->next = NULL;
    // If k >= length of list, just reassign pointers.
    } else {
      l->front = lst->front;
      l->back = lst->back;
      l->len = lst->len;
      lst->front = NULL;
      lst->back = NULL;
      lst->len = 0;
    }
  }
  return l;
}




/**
* 
* function:  lst_filter_leq
*
* description:  removes all elements of the given list (lst) which
*		are less than or equal to a given value (cutoff)
*		
*		A list containing the removed elements is returned.
*
* examples:
*
*	EX1: 	lst:  [4, 9, 2, 4, 8, 12, 7, 3]
*		cutoff:  4
*
*		after call:
*			lst:  [9, 8, 12, 7]
*			returned list:  [4, 2, 4, 3]
*
*       -----------------------------------------
*	EX2: 	lst:  [6, 5, 2, 1]
*		cutoff:  6
*
*		after call:
*			lst:  []
*	 		returned list:  [6, 5, 2, 1]
*
* REQUIREMENTS:
*
*	RUNTIME:  THETA(n) where n is the length of the given list
*
*       ORDERING:  the ordering of the returned list should be the same as
*                  in the given list
*
*       MEMORY:    for full credit, no new nodes should be allocated or deallocated;
*		   you should just "re-use" the existing nodes.  HOWEVER, you will
*		   need to allocate a LIST structure itself (i.e., for the returned
*		   list).
*			
*/
LIST * lst_filter_leq(LIST *lst, ElemType cutoff) {
  LIST* l = lst_create();
  NODE* cur = lst->front;
  NODE* prev = NULL;
  while (cur) {
    if (cur->val <= cutoff) {
      NODE* rem = cur;
      // If prev doesn't exist, it means 
      // we're removing the first node
      if (prev) {
        prev->next = cur->next;
      } else {
        lst->front = cur->next;
      }
      cur = cur->next;
      rem->next = NULL;
      // If list isn't empty...
      if (l->back) {
        l->back->next = rem;
      } else {
        l->front = rem;
      }
      l->back = rem;
      // Adjust lengths accordingly
      lst->len--;
      l->len++;
    } else {
      prev = cur;
      cur = cur->next;
    }
  }
  return l;

}

/**
* 
* function:  lst_concat
*
* description:  concatenates lists a and b; resulting
*    concatenation is reflected in list a; list b becomes
*    empty.
*
*    example:
*
*	EX1:  a: [2, 9, 1]
*	      b: [5, 1, 2]
*
*	after call:
*
*		a: [2, 9, 1, 5, 1, 2]
*		b: []
*
* REQUIREMENTS:  
*
*     runtime:  O(1)
*
*     sanity:  this operation makes sense when a and b
*		are distinct lists.  For example, we don't
*		want/allow the caller to do something like
*		this:
*
*			LIST *my_list;
*
*			lst_push_front(my_lst, 4);
*			lst_push_front(my_lst, 2);
*
*			lst_concat(my_lst, my_lst);
*
*		your implementation must detect if it is being
*		called this way.  If so the function does nothing
*		and (optionally) prints an error message to
*		stderr.
*	
*/
void lst_concat(LIST *a, LIST *b) {
  // We check to ensure a != b
  if (a != b) {
    // If a isn't empty...
    if (a->back) {
      a->back->next = b->front;
    } else {
      a->front = b->front;
    }
    // Reassign pointers
    a->back = b->back;
    a->len += b->len;
    b->front = NULL;
    b->back = NULL;
    b->len = 0;
  }
}
