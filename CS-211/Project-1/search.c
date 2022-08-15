#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>


#define NROWS 11
#define NCOLS 11
#define START_R (NROWS/2)
#define START_C (NCOLS/2)


#define NORTH 'n'
#define SOUTH 's'
#define EAST  'e'
#define WEST  'w'
#define QUIT  'q'
#define BLANK 'b'
#define ERROR 'r'

/**
 * starter code for the 'search' program/game.
 *
 * The given code takes care of two of the tasks in the program:
 *
 *      - reading and interpreting a user command via the read_cmd
 *          function.  Read the banner comment and examine the example
 *          usage of the function in main for details.
 *
 *      - handling optional command line arguments which allow a 
 *          the user (tester) to specify explicitly the location of
 *          the pot-o-gold instead of that location being randomized
 *          as in the default mode.
 *
 */

/**
 * func:  read_cmd
 * desc:  (attempts to) read a single line from standard input, and 
 *          returns one of the following:
 *
 *          NORTH : if the first non-whitespace character is either
 *                  'n' or 'N'
 *          SOUTH : if the first non-whitespace character is either
 *                  's' or 'S'
 *          EAST  : if the first non-whitespace character is either
 *                  'e' or 'E'
 *          WEST  : if the first non-whitespace character is either
 *                  'w' or 'W'
 *          QUIT  : if the first non-whitespace character is either
 *                  'q' or 'Q' OR an input line cannot be read (this
 *                  happens if EOF is read terminating the input; from 
 *                  the terminal, this happens if the user types ctrl-D 
 *                  (in UNIX at least))
 *          BLANK : if the user entered a blank/empty line
 *          ERROR : if the user entered an invalid command
 *
 */

char read_cmd() {

    char buf[128];

    // this happens when fgets reads 'EOF'.  This happens
    //   when the user types CTRL-D
    if(fgets(buf, 128, stdin) == NULL)
        return 'q';

    int n = strlen(buf);

    int i=0;

    while(i<n && isspace(buf[i]))
        i++;

    if(i==n)
        return BLANK;  // entire line is whitespace (incl newline)
    char c = buf[i];

    switch(c) {
        case 'n':
        case 'N': return NORTH;
        case 's':
        case 'S': return SOUTH;
        case 'e':
        case 'E': return EAST;
        case 'w':
        case 'W': return WEST;
        case 'q':
        case 'Q': return QUIT;
        default: 
                  return ERROR;

    }
}

/**
 * func: inrange
 * desc: simple predicate function determining whether a 
 *          given coordinate (r,c) is within the boundaries
 *          of the "board" (if yes, returns true; if no,
 *          returns false).
 */
int inrange(int r, int c) {
    if(r < 0 || c < 0 || r >= NROWS || c >= NCOLS) 
        return 0;
    else
        return 1;
}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    int g_row, g_col, p_row, p_col;
    int moves = 0;
    int randomize = 1;

    //for(int i=0; i<argc; i++) {
    //    printf(" argv[%i] : '%s'\n", i, argv[i]);
    //}
    if(argc == 3){
        int r1 = sscanf(argv[1], "%i", &g_row);  // row coord of gold
        int r2 = sscanf(argv[2], "%i", &g_col);  // row coord of gold
        if(r1==0 || r2==0 || !inrange(g_row, g_col) ||
                (g_row == START_R && g_col == START_C))
            printf("bad cmd-line args: using random location for gold\n");
        else
            randomize = 0;
    }
    else if(argc != 1) 
            printf("bad cmd-line args: using random location for gold\n");

    if(randomize) {
        g_row = rand() % 11;
        g_col = rand() % 11;
    }

    //fprintf(stderr, "pot-o-gold location: (%d, %d)\n", g_row, g_col);
    
    p_row = START_R;
    p_col = START_C;

    // demo loop...
    while(true) {
        printf("Direction: ");
        char c = read_cmd();
        
        if(c == 'q') {
            break;
        }

        int new_prow = p_row;
        int new_pcol = p_col;

        if (c == 'n') {
            moves++;
            new_prow--;   
        }
        else if (c == 's') {
            moves++;
            new_prow++;
        }
        else if (c == 'e') {
            moves++;
            new_pcol++;
        }
        else if (c == 'w') {
            moves++;
            new_pcol--;
        }
        else {
            printf("Invalid input. Try again.\n");
            continue;
        }

        if ((new_prow == g_row) && (new_pcol == g_col)) {
            printf("  HOORAY!\n\n");
            printf("Total moves: %d\n", moves);
            printf("Goodbye!\n");
            break;
        }

        if (inrange(new_prow, new_pcol)) {
            if (fabs(g_row - new_prow) < fabs(g_row - p_row) || fabs(g_col - new_pcol) < fabs(g_col - p_col)){
                printf("  GETTING WARMER!\n");
            }
            else {
                printf("  GETTING COLDER!\n");
            }
            p_row = new_prow;
            p_col = new_pcol;
        }
        else {
            printf("  OUCH!\n");
        }
    }
}
