#include <stdio.h>
#include "bpgame.h"
#include <stdlib.h>
#include <time.h>

/** TYPEDEFS / STRUCTs HERE ***/

struct bpgame{

  char** board;
  int row;
  int col;
  int score;
  
};

BPGame * bp_create(int rows, int cols){

  // out of range rows and columns
  if(rows < 0 || rows > 40 || cols < 0 || cols > 40){
    fprintf(stderr,"Invalid size of rows and columns");
    return NULL;
  }

  BPGame *b = (BPGame*)malloc(sizeof(BPGame));
  char** gameBoard = (char**)malloc(rows*sizeof(char*));
  int i,j;
  for(i = 0; i < rows; i++){
    gameBoard[i] = (char*)malloc(cols*sizeof(char));
  }


  time_t t;

  srand((unsigned)time(&t));

  for(i=0; i<rows; i++){
    for(j=0; j<cols; j++){
      int randNum = rand();
      char balloon;
      if(randNum%4 == 0){
        balloon = Red;
      }
      else if(randNum%4 == 1){
        balloon = Yellow;
      }

      else if(randNum%4 == 2){
        balloon = Blue;
      }

      else{
        balloon = Green;
      }

      gameBoard[i][j] = balloon;

    }

  }

  b->board = gameBoard;
  b->row=rows;
  b->col=cols;
  b->score=0;

  return b;


}


BPGame * bp_create_from_mtx(char mtx[][MAX_COLS], int nrows, int ncols){
  if(nrows < 0 || nrows > 40 || ncols < 0 || ncols > 40){
    fprintf(stderr,"Invalid size of rows and columns");
    return NULL;
  }

  BPGame* temp = (BPGame*)malloc(sizeof(BPGame));
  temp = bp_create(nrows,ncols);

  int i,j;
  
  for(i=0; i<nrows; i++){
    for(j=0; j<ncols; j++){
      temp->board[i][j] = mtx[i][j];
    }
  }

  return temp;

}


void bp_destroy(BPGame * b){
  int i=0;
  for(i=0; i<b->row;i++){
    free(b->board[i]);
  }
  free(b->board);
  free(b);

}


void display_border(int n){

  int i;

  printf("  +-");

  for(i=0;i<n*2-1;i++){

    printf("-");

  }

  printf("-+\n");

}


void display_row(char* row,int n){

  printf("| ");

  int i;

  for(i=0; i<n; i++){

    printf("%c ",row[i]);

  }

  printf("|\n");

}


void bp_display_STD(BPGame *b){

  for(int i = 0; i < b->row; i++){

    for(int j = 0; j < b->col; j++){

      printf("%c", b->board[i][j]);

    }

    printf("\n");

  }

}


void display_col(BPGame *b){

  int i;

  printf("    ");

  for(i=0; i<b->col; i++){

    printf("%d ",i/10);

  }

  printf("\n    ");

  for(i=0; i<b->col; i++){

    printf("%d ",i%10);

  }

  printf("\n");

}


void bp_display(BPGame * b){

  //we need to create the borders

  display_border(b->col);

  int i;

  for(i=0; i<b->row; i++){

    if(i > 9){

      printf("%d",i);

    }

    else{

      printf("%d ",i);

    }

    display_row(b->board[i],b->col);

  }

  display_border(b->col);

  display_col(b);

}


void pop(BPGame *b,int r,int c,char color,int* count){

  if(r-1>=0 && b->board[r-1][c] == color){

    b->board[r][c] = '.';

    //b->board[r-1][c] ='.';

    (*count)++;

    //printf("first %d\n",*count);

    pop(b,r-1,c,color,count);

  }

  if(r+1<b->row && b->board[r+1][c] == color){

    b->board[r][c] = '.';

   // b->board[r+1][c] = '.';

    (*count)++;

    //printf("second %d\n",*count);

    pop(b,r+1,c,color,count);

  }

  if(c-1>=0 && b->board[r][c-1] == color){

    b->board[r][c] = '.';

    //b->board[r][c-1] = '.';

    (*count)++;

    //printf("third %d\n",*count);

    pop(b,r,c-1,color,count);

  }

  if(c+1<b->col && b->board[r][c+1] == color){

    b->board[r][c] = '.';

    //b->board[r][c+1] = '.';

    (*count)++;

    //printf("fourth %d\n",*count);

    pop(b,r,c+1,color,count);

  }

  if(b->board[r][c] != '.' && *count > 0){

    b->board[r][c] = '.';

    //printf("fifth %d\n",*count);

  }

}


int bp_pop(BPGame * b, int r, int c){

  if(b->board[r][c] == '.'){

    return 0;

  }

  int count=0; 

  pop(b,r,c,b->board[r][c],&count);

  if(count == 0){

    return 0;

  }

  b->score = b->score + count*(count+1);

  return count+1;

}


void swapVals(char **m, int n, int row, int col){

  char temp;

  m[row][col] = temp;

  m[row][col] = m[row-1][col];

  m[row-1][col] = temp;

}


int isValid(char** m, int row, int col){

  int i,j;

  for(i=0;i<row-1;i++){

    for(j=0;j<col;j++){

      if(m[i][j] == '.' && m[i+1][j] != '.'){

        return 0;

      }

    }

  }

  return 1;

}


int bp_is_compact(BPGame *b){

  return isValid(b->board,b->row,b->col);

}


void bp_float_one_step(BPGame *b){

  int i,j;

  int col = b->col;

  int row = b->row;

  char** m = b->board;

  if(col<=1){

    return;

  }

  for(i=0;i<row-1;i++){

    for(j=0;j<col;j++){

      if(m[i][j] == '.' && m[i+1][j] != '.'){

        m[i][j] = m[i+1][j]; 

        m[i+1][j] = '.';

      }

    }

  }

}


int bp_score(BPGame * b){

  return b->score;

}



int bp_get_balloon(BPGame * b, int r, int c){

  if(r<0 || r>b->row || c<0 || c>b->col){

    return -1;

  }

  return b->board[r][c];

}



int bp_can_pop(BPGame * b){

  int i,j;

  for(i=1; i<b->row-2;i++){

    for(j=1;j<b->col-2;j++){

      char balloon = b->board[i][j];

      if((balloon == b->board[i+1][j] || balloon == b->board[i-1][j] || balloon == b->board[i][j+1] || balloon == b->board[i][j-1]) && balloon != '.'){

        return 1;

      }

    }

  }

  if(b->row < 2 || b->col < 2){

    return 0;

  }

  if((b->board[0][0] == b->board[1][0] || b->board[0][0] == b->board[0][1]) && b->board[0][0] != '.'){

    return 1;

  }

  if((b->board[b->row-1][b->col-1] == b->board[b->row-1][b->col-2] || b->board[b->row-1][b->col-1] == b->board[b->row-2][b->col-1]) && b->board[b->row-1][b->col-1] != '.'){

    return 1;

  }

  if((b->board[b->row-1][0] == b->board[b->row-2][0] || b->board[b->row-1][0] == b->board[b->row-1][1]) && b->board[b->row-1][0] != '.'){

    return 1;

  }

  if((b->board[0][b->col-1] == b->board[0][b->col-2] || b->board[0][b->col-1] == b->board[1][b->col-1]) && b->board[0][b->col-1] != '.'){

    return 1;

  }

  return 0;

}



int bp_undo(BPGame * b){}
