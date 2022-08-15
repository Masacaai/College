// File: bpgame.c
// Author: Jash Shah                UIC Spring 2022
// Author: Aaqel Shaik Abdul Mazeed UIC Spring 2022

/** #include statements... **/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bpgame.h"

/** TYPEDEFS / STRUCTs HERE ***/
struct bpgame {
   // YOU DECIDE WHAT TO PUT IN HERE TO CAPTURE THE STATE OF
   //   A "RUN" OF THE GAME.....
   char** board;
   int rows;
   int cols;
   int score;
   BPGame * prev; 
};

/*** IMPLEMENTATION OF bp_XXXX FUNCTIONS HERE  ****/
BPGame * bp_create(int nrows, int ncols) {
   BPGame *b;
   char colors[4] = {Red, Blue, Green, Yellow};

   // out of range rows and columns
   if(nrows < 0 || nrows > MAX_ROWS || ncols < 0 || ncols > MAX_COLS){
      fprintf(stderr,"Invalid size of rows and columns");
      return NULL;
   }

   b = malloc(sizeof(BPGame));
   char** gameBoard = malloc(nrows*sizeof(char*));
   for(int i = 0; i < nrows; i++){
      gameBoard[i] = malloc(ncols*sizeof(char));
   }

   time_t t;
   srand((unsigned) time(&t));

   for(int i = 0; i < nrows; i++){
      for(int j = 0; j < ncols; j++){
         gameBoard[i][j] = colors[rand() % 4];
      }
   }

   b->board = gameBoard;
   b->rows = nrows;
   b->cols = ncols;
   b->score = 0;
   b->prev = NULL;
   return b;
}

BPGame * bp_create_from_mtx(char mtx[][MAX_COLS], int nrows, int ncols){
   BPGame *b;

   if (nrows < 0 || nrows > MAX_ROWS || ncols < 0 || ncols > MAX_COLS){
      fprintf(stderr,"Invalid size of rows and columns");
      return NULL;
   }

   b = malloc(sizeof(BPGame));
   char** gameBoard = malloc(nrows*sizeof(char*));
   for (int i = 0; i < nrows; i++){
      gameBoard[i] = malloc(ncols*sizeof(char));
   }

   for (int i = 0; i < nrows; i++){
      for(int j = 0; j < ncols; j++){
         gameBoard[i][j] = mtx[i][j];
      }
   }

   b->board = gameBoard;
   b->rows = nrows;
   b->cols = ncols;
   b->score = 0;
   b->prev = NULL;
   return b;
}

void bp_destroy(BPGame * b){
   for (int i = 0; i < b->rows; i++){
      free(b->board[i]);
   }
   
   free(b->board);
   free(b);
}

void display_border(int n){
   printf("  +-");
   for (int i = 0; i < n*2-1; i++){
      printf("-");
   }
   printf("-+\n");
}

void display_row(char* row, int n){
   printf("| ");
   for (int i = 0; i < n; i++){
      printf("%c ",row[i]);
   }
   printf("|\n");
}

// Debug function
void bp_display_STD(BPGame *b){
   for (int i = 0; i < b->rows; i++){
      for (int j = 0; j < b->cols; j++){
         printf("%c", b->board[i][j]);
      }
      printf("\n");
   }
}

void display_col(int n){
   printf("    ");
   for (int i = 0; i < n; i++){
      printf("%d ",i/10);
   }
   printf("\n    ");

   for (int i = 0; i < n; i++){
      printf("%d ",i%10);
   }
   printf("\n");
}


void bp_display(BPGame * b){

   //we need to create the borders
   display_border(b->cols);
  
   for (int i = 0; i < b->rows; i++){
      if (i > 50) {
         break;
      }
      if (i > 9){
         printf("%d",i);
      }
      else{
         printf("%d ",i);
      }
      display_row(b->board[i],b->cols);
   }

   display_border(b->cols);
   display_col(b->cols);
}

void addNode(BPGame * b) {
   // Create new node
   BPGame *bNew = malloc(sizeof(BPGame));
   char** gameBoard = malloc(b->rows * sizeof(char*));
   for (int i = 0; i < b->rows; i++){
      gameBoard[i] = malloc(b->cols * sizeof(char));
   }

   for (int i = 0; i < b->rows; i++){
      for(int j = 0; j < b->cols; j++){
         gameBoard[i][j] = b->board[i][j];
      }
   }
   // Copy values to new node
   bNew->board = gameBoard;
   bNew->rows = b->rows;
   bNew->cols = b->cols;
   bNew->score = b->score;
   // Reassign pointers
   bNew->prev = b->prev;
   b->prev = bNew;
}

void pop(BPGame *b, int r, int c, int *count){
   char current = b->board[r][c];

   // Check balloon on the top
   if (r - 1 >= 0 && b->board[r-1][c] == current && b->board[r-1][c] != None){
      if (b->board[r][c] != None) {
         b->board[r][c] = None;
         (*count)++;   
      }
      pop(b, r-1, c, count);
   }
   // Check balloon on the bottom
   if (r + 1 < b->rows && b->board[r+1][c] == current && b->board[r+1][c] != None){
      if (b->board[r][c] != None) {
         b->board[r][c] = None;
         (*count)++;
      }
      pop(b, r+1, c, count);
   }
   // Check balloon on the left
   if (c - 1 >= 0 && b->board[r][c-1] == current && b->board[r][c-1] != None){
      if (b->board[r][c] != None) {
         b->board[r][c] = None;
         (*count)++;
      }
      pop(b, r, c-1, count);
   }
   // Check balloon on the right
   if (c + 1 < b->cols && b->board[r][c+1] == current && b->board[r][c+1] != None){
      if (b->board[r][c] != None) {
         b->board[r][c] = None;
         (*count)++;
      }
      pop(b, r, c+1, count);
   }
   // If no nearby balloons are found, pop current
   // balloon if it's not the first balloon.
   if (b->board[r][c] != None && *count > 0){
      b->board[r][c] = None;
      (*count)++;
   }
}

int bp_pop(BPGame * b, int r, int c){
   int count = 0;
   if(b->board[r][c] == None){
      return 0;
   }
   addNode(b);
   pop(b, r, c, &count);
   if (count <= 0) {
      bp_undo(b);
   }
   b->score += count * (count - 1);
   return count;
}

int bp_is_compact(BPGame *b){
   for (int i = 0; i < b->rows - 1; i++){
      for (int j = 0; j < b->cols; j++){
         if (b->board[i][j] == None && b->board[i+1][j] != None){
            return 0;
         }
      }
   }
   return 1;
}

void bp_float_one_step(BPGame *b){
  if(b->cols <= 1){
    return;
  }

   for(int i = 0; i < b->rows - 1; i++){
      for(int j = 0; j < b->cols; j++){
         if(b->board[i][j] == None && b->board[i+1][j] != None){
            b->board[i][j] = b->board[i+1][j]; 
            b->board[i+1][j] = None;
         }
      }
   }
}

int bp_score(BPGame * b){
   return b->score;
}

int bp_get_balloon(BPGame * b, int r, int c){
   if(r < 0 || r > b->rows || c < 0 || c > b->cols){
      return -1;
   }
   return b->board[r][c];
}

int bp_can_pop(BPGame * b){
   int r = b->rows;
   int c = b->cols;
   char **m = b->board;

   if (r < 2 || c < 2){
      return 0;
   }

   // Checks the insides of the matrix
   for(int i = 1; i < r - 2; i++){
      for(int j = 1; j < c - 2; j++){
         if((m[i][j] == m[i+1][j] ||
             m[i][j] == m[i-1][j] ||
             m[i][j] == m[i][j+1] ||
             m[i][j] == m[i][j-1])&&
             m[i][j] != None){
                return 1;
         }
      }
   }
   // Checks the corners of the matrix
   if((m[0][0] == m[1][0] ||
       m[0][0] == m[0][1])&&
       m[0][0] != None){
          return 1;
   }
   if((m[r - 1][c - 1] == m[r - 1][c - 2] ||
       m[r - 1][c - 1] == m[r - 2][c - 1])&&
       m[r - 1][c - 1] != None){
          return 1;
   }
   if((m[r - 1][0] == m[r - 2][0] ||
       m[r - 1][0] == m[r - 1][1])&&
       m[r - 1][0] != None){
          return 1;
   }
   if((m[0][c - 1] == m[0][c - 2] ||
       m[0][c - 1] == m[1][c - 1])&&
       m[0][c - 1] != None){
          return 1;
   }
   return 0;
}

int bp_undo(BPGame * b) {
   if (b->prev == NULL) {
      return 0;
   }

   BPGame *previous = b->prev;
   // Change current values to match previous node
   for (int i = 0; i < b->rows; i++){
      for(int j = 0; j < b->cols; j++){
         b->board[i][j] = b->prev->board[i][j];
      }
   }
   b->rows = b->prev->rows;
   b->cols = b->prev->cols;
   b->score = b->prev->score;
   // Reassign pointers
   b->prev = b->prev->prev;
   // Destroy previous node;
   bp_destroy(previous);
   previous = NULL;
   return 1;
}



