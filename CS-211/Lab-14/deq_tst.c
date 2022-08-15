
#include <stdio.h>
#include <stdlib.h>
#include "deq.c"

// very incomplete small test program...

void all_sanity(DEQ *q) {
  if(deq_sanity1(q)) 
    printf("sanity1: PASSED\n");
  else
    printf("sanity1: FAILED\n");
  if(deq_sanity2(q)) 
    printf("sanity2: PASSED\n");
  else
    printf("sanity2: FAILED\n");
  if(deq_sanity3(q)) 
    printf("sanity3: PASSED\n");
  else
    printf("sanity3: FAILED\n");
  if(deq_sanity4(q)) 
    printf("sanity4: PASSED\n");
  else
    printf("sanity4: FAILED\n");
}


int main() {
DEQ *q1;
int i, x;

  q1 = deq_create();

  deq_push_front(q1, 0);
  deq_push_back(q1, 1);

  deq_pop_back(q1, &x);
  deq_push_back(q1, 1);

  printf("START CHECKPOINT 1\n");
  printf("  START SANITY CHECKS...\n");
  all_sanity(q1);
  printf("  END SANITY CHECKS...\n");

  printf("ACTUAL:   ");
  deq_print(q1);
  printf("EXPECTED:  [ 0  1 ]\n");

  printf("END CHECKPOINT 1\n\n");

  DEQ *q2 = deq_create();

  for(i=0; i<5; i++) {
     deq_push_front(q2, i);
  }
  for(i=0; i<5; i++) {
     deq_push_back(q2, i);
  }

  printf("START CHECKPOINT 2\n");
  printf("  START SANITY CHECKS...\n");
  all_sanity(q2);
  printf("  END SANITY CHECKS...\n");

  printf("ACTUAL:   ");
  deq_print(q2);
  printf("EXPECTED:  [ 4  3  2  1  0  0  1  2  3  4 ]\n");
  printf("END CHECKPOINT 2\n\n");

  // MORE TESTS!!!
  printf("START CHECKPOINT 3\n");
  printf("  START SANITY CHECKS...\n");
  all_sanity(q2);
  printf("  END SANITY CHECKS...\n");
  
  for (i = 0; i < 5; ++i) {
    deq_pop_back(q2, &x);
  }

  printf("ACTUAL:   ");
  deq_print_rev(q2);
  printf("EXPECTED: [ 0  1  2  3  4 ]\n");
  
  printf("END CHECKPOINT 3\n\n");

  printf("START CHECKPOINT 4\n");
  printf("  START SANITY CHECKS...\n");
  all_sanity(q2);
  printf("  END SANITY CHECKS...\n");

  for (i = 0; i < 2; ++i) {
    deq_pop_front(q2, &x);
  }

  printf("ACTUAL:   ");
  deq_print_rev(q2);
  printf("EXPECTED: [ 0  1  2 ]\n");

  printf("END CHECKPOINT 4\n\n");

  printf("START CHECKPOINT 5\n");
  printf("  START SANITY CHECKS...\n");
  all_sanity(q2);
  printf("  END SANITY CHECKS...\n");

  for (i = 0; i < 2; ++i) {
    deq_push_front(q2, i);
  }

  printf("ACTUAL:   ");
  deq_print_rev(q2);
  printf("EXPECTED: [ 0  1  2  0  1 ]\n");

  printf("END CHECKPOINT 5\n\n");

  printf("START CHECKPOINT 6\n");
  printf("  START SANITY CHECKS...\n");
  all_sanity(q2);
  printf("  END SANITY CHECKS...\n");

  for (i = 0; i < 2; ++i) {
    deq_push_back(q2, i);
  }

  printf("ACTUAL:   ");
  deq_print_rev(q2);
  printf("EXPECTED: [ 1  0  0  1  2  0  1 ]\n");

  printf("END CHECKPOINT 6\n\n");
  deq_free(q1);
  deq_free(q2);
  return 0;
}
  
