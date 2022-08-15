

//

/** ElemType may be changed for application
 * specific needs.
 *
 * However, it should be a numeric type.
 */

typedef int ElemType;
#define FORMAT " %i "
#define DEFAULT 0

// hidden implementation of deq_struct
typedef struct deq_struct DEQ;

extern DEQ *deq_create(); 
extern void deq_free(DEQ *q);
extern void deq_print(DEQ *q); 

/* TODO */
void deq_print_rev(DEQ *q); 


extern void deq_push_front(DEQ *q, ElemType val); 

/* TODO */
extern void deq_push_back(DEQ *q, ElemType val); 

/** TODO
 * function:  deq_pop_front
 *
 * description:  
 *   if deq is non-empty:  removes FIRST element from deq and 
 *      stores result in *val and returns 1 (TRUE)
 *
 * RUNTIME:  CONSTANT
 */
extern int deq_pop_front(DEQ *q, ElemType *val); 

/** TODO
 * function:  deq_pop_back
 *
 * description:  
 *   if deq is non-empty:  removes last element from deq and 
 *      stores result in *val and returns 1 (TRUE)
 *
 * RUNTIME:  CONSTANT
 */
extern int deq_pop_back(DEQ *q, ElemType *val); 


// sanity checker functions - DONE
extern int deq_sanity1(DEQ *l);
extern int deq_sanity2(DEQ *l);
extern int deq_sanity3(DEQ *l);
extern int deq_sanity4(DEQ *l);



