
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "prog2.h"



/**
* 
*  Function "stubs" for Assignment 2 exercises.
*
*  See prog2.h for specifications of function behavior.
*
*/



/***********************************************
*                                             **
*   MATRIX FUNCTIONS                          **
*                                             **
*   NOTE:  parameter n ALWAYS expresses the   **
*     dimensions of the square matrix in      **
*     question.                               **
*                                             **
***********************************************/
char ** alloc_square_mtx(int n) {
  char **m;

  m = malloc(n*sizeof(char *));
  for (int i = 0; i < n; ++i) {
    m[i] = malloc(n*sizeof(char));
  }
  
  return m;
}

void free_square_mtx(char **m, int n) {

  for (int i = 0; i < n; ++i) {
    free(m[i]);
  }
  free(m);
}

void pop_mtx_alpha(char **m, int n){
  char str[] =  "abcdefghijklmnopqrstuvwxyz";
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      m[i][j] = str[rand() % 26];
    }
  }

}


void display_mtx(char **m, int n){
  for(int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      printf("%c", m[i][j]);
    }
    printf("\n");
  }
}

void swap_rows(char **m, int n, int r1, int r2){
  if (r1 < n && r2 < n) {
    char *tmp;
    
    tmp = m[r1];
    m[r1] = m[r2];
    m[r2] = tmp;
  }
}

void swap_cols(char **m, int n, int c1, int c2){
  if (c1 < n && c2 < n) {
    for (int i = 0; i < n; ++i) {
      char tmp;

      tmp = m[i][c1];
      m[i][c1] = m[i][c2];
      m[i][c2] = tmp;
    }
  }
}


void rotate_right(char **m, int n){

  // Reverses each row
  for (int i = 0; i < n / 2; ++i) {
    swap_cols(m,n,i,n-1-i);
  }
  
  // Swaps values along the diagonal
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n - 1 - i; ++j) {
      char tmp;

      tmp = m[i][j];
      m[i][j] = m[n-1-j][n-1-i];
      m[n-1-j][n-1-i] = tmp;
      
    }
  }
}


void floating_boulders(char **m, int n, int nb){
  if (nb < 0) {nb = 0;}
  if (nb > n * n) {nb = n*n;}

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      m[i][j] = '.';
    }
  }

  while (nb != 0) {
    int i = rand() % n;
    int j = rand() % n;
    if (m[i][j] != '#') {
      m[i][j] = '#';
      --nb;
    };
  } 
}


void mountains(char **m, int n){
  for (int i = 0; i < n; ++i) {
    for (int j = 0, height = rand() % n; j < n; ++j) {
      m[j][i] = (j < height) ? '.' : '#';
    }
  } 
}



void sink(char **m, int n){
  for (int i = n - 1; i > 0; --i) {
    for (int j = 0; j < n; ++j) {
      m[i][j] = m[i-1][j];
    }
  }

  for (int i = 0; i < n; ++i) {
    m[0][i] = '.';
  }
}



void gravity(char **m, int n){
  for (int i = 0; i < n; ++i) {
    int count = 0;
    for (int j = n - 1; j >= 0; --j) {
      if (m[j][i] == '.') {
        count++;
      }
      else {
        char tmp;

        tmp = m[j][i];
        m[j][i] = m[j + count][i];
        m[j + count][i] = tmp;
        j = j + count;
        count = 0;
      }
    }
  } 
}




/***********************************************
*                                             **
*   STRING FUNCTIONS                          **
*                                             **
***********************************************/


void str_trim(char *s) {
  int lead = 0;
  int trail = 0;
  int length = strlen(s);

  for (int i = 0; i < strlen(s); ++i) {
    if (isspace(s[i])) {lead++;}
    else {break;}
  }

  for (int i = 0; i < strlen(s) - lead; ++i) {
    char tmp;

    tmp = s[i];
    s[i] = s[lead + i];
    s[lead + i] = tmp;
  }

  for (int i = strlen(s) - 1; i >= 0; --i) {
    if (isspace(s[i])) {trail++;}
    else {break;}
  }

  s[length - trail] = '\0';
}


int str_search(char *s, char *pattern) {
  
  if (strlen(pattern) > strlen(s)) {
    return -1;
  }

  for (int i = 0 ; i < strlen(s); ++i) {
    int found = 1;
    for (int j = 0; j < strlen(pattern); ++j) {
      if (s[i + j] != pattern[j]) {
        found = 0;
        break;
      }
    }

    if (found) {return i;}
  }
  return -1;  

}





#ifndef _LIB  // DO NOT REMOVE THIS LINE!!!
              // IT DOESN"T CHANGE HOW YOUR PROGRAM
              // WORKS, BUT IT GIVES US A WAY TO CALL
              // YOUR FUNCTIONS FROM OUR CODE FOR
              // TESTING

/**
* Write a test driver in main below to exercise and
*   your function implementations.
*
* Think carefully about your test cases!
*/
int main(){
  srand(1);
  int choice = 1;
  char **m;
  int n;
  printf("Welcome to ASCII-Unlimited's test driver!\n");
  
  while (choice) {
    printf("\nChoose from the following options below:\n");
    printf("1. Allocate square matrix\n");
    printf("2. Free square matrix\n");
    printf("3. Populate matrix with alphabets\n");
    printf("4. Display matrix\n");
    printf("5. Swap rows\n");
    printf("6. Swap columns\n");
    printf("7. Rotate right\n");
    printf("8. Populate matrix with floating boulders\n");
    printf("9. Populate matrix with mountains\n");
    printf("10. Sink all elements in matrix\n");
    printf("11. Toggle gravity for floating elements\n");
    printf("12. Trim a string\n");
    printf("13. Search a string\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
    scanf("%i", &choice);
    printf("\n");

    if (choice == 1) {
      printf("Enter N: ");
      scanf("%i", &n);
      printf("\n");

      m = alloc_square_mtx(n);
    }
    if (choice == 2) {free_square_mtx(m, n);}
    if (choice == 3) {pop_mtx_alpha(m, n);}
    if (choice == 4) {display_mtx(m, n);}
    if (choice == 5) {
      int r1, r2;
      printf("Enter row 1: ");
      scanf("%i", &r1);
      printf("\n");

      printf("Enter row 2: ");
      scanf("%i", &r2);
      printf("\n");

      swap_rows(m, n, r1, r2);
    }
    if (choice == 6) {
      int c1, c2;
      printf("Enter col 1: ");
      scanf("%i", &c1);
      printf("\n");

      printf("Enter col 2: ");
      scanf("%i", &c2);
      printf("\n");
      
      swap_cols(m, n, c1, c2);
    }
    if (choice == 7) {rotate_right(m, n);}
    if (choice == 8) {
      int nb;
      printf("Enter number of boulders: ");
      scanf("%i", &nb);
      printf("\n");

      floating_boulders(m, n, nb);
    }
    if (choice == 9) {mountains(m, n);}
    if (choice == 10) {sink(m, n);}
    if (choice == 11) {gravity(m, n);}
    if (choice == 12) {
      int len;
      printf("Enter length of string: ");
      scanf("%i", &len);
      printf("\n");

      char s[len];
      printf("Enter string: ");
      scanf("%s", &s);
      printf("\n");

      str_trim(s);
      printf("Trimmed string: %s\n", s);
    }
    if (choice == 13) {
      int len;
      printf("Enter length of string: ");
      scanf("%i", &len);
      printf("\n");

      char s[len];
      printf("Enter string: ");
      scanf("%s", &s);
      printf("\n");

      printf("Enter length of pattern: ");
      scanf("%i", &len);
      printf("\n");

      char pattern[len];
      printf("Enter pattern: ");
      scanf("%s", &pattern);
      printf("\n");

      printf("Occurance of pattern in string at: %i\n", str_search(s, pattern));
    }

  }

  printf("Goodbye!\n");
}


#endif        // DO NOT REMOVE THIS LINE!!!
