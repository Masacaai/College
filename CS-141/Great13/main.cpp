/* ----------------------------------------------------------------------
    Program 2: Great 13
        Peg puzzle. Jump pegs to try and leave only a single peg.

    Course: CS 141, Fall 2021. Tues 9 AM lab
    System: Fedora 34 using JetBrains CLion
    Author: Mohammed Aaqel Shaik Abdul Mazeed

    Running the program looks like:

        Class:   CS 141, Fall '21
        Program: #2 Great 13

        Make a series of jumps until there is a single piece left in the
        middle. On each move you must jump an adjacent piece into an empty
        square, jumping horizontally, vertically, or diagonally.

             Board    Position
               #          A
             # # #      B C D
           # # . # #  E F G H I
             # # #      J K L
               #          M

        1. Enter position to move from, piece to jump, and destination (e.g. EFG): efg
             Board    Position
               #          A
             # # #      B C D
           . . # # #  E F G H I
             # # #      J K L
               #          M

        2. Enter position to move from, piece to jump, and destination (e.g. EFG):

        . . .
   ----------------------------------------------------------------------
*/
#include <iostream>
#include <cctype>   // for toupper()
using namespace std;

// Global variables for the pieces are allowed for this program,
// but will generally not be allowed in the future.
// You will likely want to declare global variables at least for the following:
//   - 13 board pieces
//   - The letter positions you are moving from, jumping over, and moving to
//   - The number of pieces on the board (to know when there is a win)
// ...
char pA, pB, pC, pD, pE, pF, pG, pH, pI, pJ, pK, pL, pM; // Board position variables
char moveFrom, jumpOver, moveTo; // User-input variables
int numberOfPieces; // Number of pieces on board (Starts at 12 when initialized)
int moveNumber; // Move number ( Starts at 1 when initialized)

// ----------------------------------------------------------------------
// Display the game instructions.
void displayInstructions()
{
    cout << "Class: CS 141             \n"
         << "Program: #2 Great 13      \n"
         << "  \n"
         << "Make a series of jumps until there is a single piece left in the   \n"
         << "middle. On each move you must jump an adjacent piece into an empty \n"
         << "square, jumping horizontally, vertically, or diagonally.           \n"
         << "Input of 'R' resets the board back to the beginning, and input of  \n"
         << "'X' exits the game.'   \n"
         << endl;
} //end displayInstructions()


// ----------------------------------------------------------------------
// Display the board, using the global variables pA..pM
void displayBoard()
{
    cout <<"\n "
         <<                 "    Board   " <<            " Position \n"
         <<"       "             << pA <<             "          A    \n"
         <<"     " <<      pB<<" "<<pC<<" "<<pD<<       "      B C D  \n"
         <<"   "<<pE<<" "<<pF<<" "<<pG<<" "<<pH<<" "<<pI<<"  E F G H I\n"
         <<"     " <<      pJ<<" "<<pK<<" "<<pL<<       "      J K L  \n"
         <<"       "             << pM <<             "          M    \n"
         << endl;
} //end displayBoard()

// Initialize the game variables
void initializeGame() {

    // Set board values to the default starting position
    pA = '#', pB = pA, pC = pA, pD = pA, pE = pA, pF = pA, pH = pA, pI = pA, pJ = pA, pK = pA, pL = pA, pM = pA;
    pG = '.';

    numberOfPieces = 12;
    moveNumber = 1;
}

// Check adjacency of the values entered by user and returns a corresponding boolean value
bool checkAdjacency() {

    // The if statement checks for all possible valid moves
    if ((moveFrom == 'A' && jumpOver == 'B' && moveTo == 'E') ||
        (moveFrom == 'A' && jumpOver == 'C' && moveTo == 'G') ||
        (moveFrom == 'A' && jumpOver == 'D' && moveTo == 'I') ||
        (moveFrom == 'B' && jumpOver == 'C' && moveTo == 'D') ||
        (moveFrom == 'B' && jumpOver == 'G' && moveTo == 'L') ||
        (moveFrom == 'B' && jumpOver == 'F' && moveTo == 'J') ||
        (moveFrom == 'C' && jumpOver == 'G' && moveTo == 'K') ||
        (moveFrom == 'D' && jumpOver == 'C' && moveTo == 'B') ||
        (moveFrom == 'D' && jumpOver == 'G' && moveTo == 'J') ||
        (moveFrom == 'D' && jumpOver == 'H' && moveTo == 'L') ||
        (moveFrom == 'E' && jumpOver == 'B' && moveTo == 'A') ||
        (moveFrom == 'E' && jumpOver == 'F' && moveTo == 'G') ||
        (moveFrom == 'E' && jumpOver == 'J' && moveTo == 'M') ||
        (moveFrom == 'F' && jumpOver == 'G' && moveTo == 'H') ||
        (moveFrom == 'G' && jumpOver == 'C' && moveTo == 'A') ||
        (moveFrom == 'G' && jumpOver == 'H' && moveTo == 'I') ||
        (moveFrom == 'G' && jumpOver == 'K' && moveTo == 'M') ||
        (moveFrom == 'G' && jumpOver == 'F' && moveTo == 'E') ||
        (moveFrom == 'H' && jumpOver == 'G' && moveTo == 'F') ||
        (moveFrom == 'I' && jumpOver == 'D' && moveTo == 'A') ||
        (moveFrom == 'I' && jumpOver == 'H' && moveTo == 'G') ||
        (moveFrom == 'I' && jumpOver == 'L' && moveTo == 'M') ||
        (moveFrom == 'J' && jumpOver == 'F' && moveTo == 'B') ||
        (moveFrom == 'J' && jumpOver == 'G' && moveTo == 'D') ||
        (moveFrom == 'J' && jumpOver == 'K' && moveTo == 'L') ||
        (moveFrom == 'K' && jumpOver == 'G' && moveTo == 'C') ||
        (moveFrom == 'L' && jumpOver == 'H' && moveTo == 'D') ||
        (moveFrom == 'L' && jumpOver == 'G' && moveTo == 'B') ||
        (moveFrom == 'L' && jumpOver == 'K' && moveTo == 'J') ||
        (moveFrom == 'M' && jumpOver == 'J' && moveTo == 'E') ||
        (moveFrom == 'M' && jumpOver == 'K' && moveTo == 'G') ||
        (moveFrom == 'M' && jumpOver == 'L' && moveTo == 'I')) {
        return true;
    }
    else {
        return false;
    }
}

// Check if the moveFrom position has a piece on it
bool checkMoveFrom(){
    char fromPos;

    // Check for input value and select the corresponding position variable
    if (moveFrom == 'A'){ fromPos = pA; }
    if (moveFrom == 'B'){ fromPos = pB; }
    if (moveFrom == 'C'){ fromPos = pC; }
    if (moveFrom == 'D'){ fromPos = pD; }
    if (moveFrom == 'E'){ fromPos = pE; }
    if (moveFrom == 'F'){ fromPos = pF; }
    if (moveFrom == 'G'){ fromPos = pG; }
    if (moveFrom == 'H'){ fromPos = pH; }
    if (moveFrom == 'I'){ fromPos = pI; }
    if (moveFrom == 'J'){ fromPos = pJ; }
    if (moveFrom == 'K'){ fromPos = pK; }
    if (moveFrom == 'L'){ fromPos = pL; }
    if (moveFrom == 'M'){ fromPos = pM; }

    if (fromPos == '#'){
        return true;
    }
    else {
        return false;
    }
}

// Check if the jumpOver position has a piece on it
bool checkJumpOver(){
    char jumpPos;

    // Check for input value and select the corresponding position variable
    if (jumpOver == 'B'){ jumpPos = pB; }
    if (jumpOver == 'C'){ jumpPos = pC; }
    if (jumpOver == 'D'){ jumpPos = pD; }
    if (jumpOver == 'F'){ jumpPos = pF; }
    if (jumpOver == 'G'){ jumpPos = pG; }
    if (jumpOver == 'H'){ jumpPos = pH; }
    if (jumpOver == 'J'){ jumpPos = pJ; }
    if (jumpOver == 'K'){ jumpPos = pK; }
    if (jumpOver == 'L'){ jumpPos = pL; }

    if (jumpPos == '#'){
        return true;
    }
    else {
        return false;
    }
}

// Checks if the moveTo position is empty
bool checkMoveTo(){
    char toPos;

    // Check for input value and select the corresponding position variable
    if (moveTo == 'A'){ toPos = pA; }
    if (moveTo == 'B'){ toPos = pB; }
    if (moveTo == 'C'){ toPos = pC; }
    if (moveTo == 'D'){ toPos = pD; }
    if (moveTo == 'E'){ toPos = pE; }
    if (moveTo == 'F'){ toPos = pF; }
    if (moveTo == 'G'){ toPos = pG; }
    if (moveTo == 'H'){ toPos = pH; }
    if (moveTo == 'I'){ toPos = pI; }
    if (moveTo == 'J'){ toPos = pJ; }
    if (moveTo == 'K'){ toPos = pK; }
    if (moveTo == 'L'){ toPos = pL; }
    if (moveTo == 'M'){ toPos = pM; }

    if (toPos == '.'){
        return true;
    }
    else {
        return false;
    }
}

// Makes the desired move and updates affected variables
void makeMove(){
    if (moveFrom == 'A'){pA = '.'; }
    if (moveTo == 'A'){ pA = '#'; }
    if ((moveFrom == 'B') || (jumpOver == 'B')){ pB = '.'; }
    if (moveTo == 'B'){ pB = '#'; }
    if ((moveFrom == 'C') || (jumpOver == 'C')){ pC = '.'; }
    if (moveTo == 'C'){ pC = '#'; }
    if ((moveFrom == 'D') || (jumpOver == 'D')){ pD = '.'; }
    if (moveTo == 'D'){ pD = '#'; }
    if (moveFrom == 'E'){ pE = '.'; }
    if (moveTo == 'E'){ pE = '#'; }
    if ((moveFrom == 'F') || (jumpOver == 'F')){ pF = '.'; }
    if (moveTo == 'F'){ pF = '#'; }
    if ((moveFrom == 'G') || (jumpOver == 'G')){ pG = '.'; }
    if (moveTo == 'G'){ pG = '#'; }
    if ((moveFrom == 'H') || (jumpOver == 'H')){ pH = '.'; }
    if (moveTo == 'H'){ pH = '#'; }
    if (moveFrom == 'I'){ pI = '.'; }
    if (moveTo == 'I'){ pI = '#'; }
    if ((moveFrom == 'J') || (jumpOver == 'J')){ pJ = '.'; }
    if (moveTo == 'J'){ pJ = '#'; }
    if ((moveFrom == 'K') || (jumpOver == 'K')){ pK = '.'; }
    if (moveTo == 'K'){ pK = '#'; }
    if ((moveFrom == 'L') || (jumpOver == 'L')){ pL = '.'; }
    if (moveTo == 'L'){ pL = '#'; }
    if (moveFrom == 'M'){ pM = '.'; }
    if (moveTo == 'M'){ pM = '#'; }
    numberOfPieces--;
}

// ----------------------------------------------------------------------
// Main section of the program, containing the game play loop
int main() {

    displayInstructions(); // Display instructions
    initializeGame(); // Initialize game

    // Game play loop
    displayBoard();
    while ( numberOfPieces > 1 ) {
        cout << moveNumber << ". "
             << "Enter positions from, jump, and to (e.g. EFG): ";
        cin >> moveFrom;                // Read just the first user input, handling inputs 'X' or 'R'
        moveFrom = toupper( moveFrom);  // Fold input into upper case to simplify later comparisons

        // If 'X' to exit was chosen, break out of game play loop
        // ...
        if (moveFrom == 'X'){
            cout << "Exiting" << endl;
            break;
        }

        // If 'R' to reset the board was chosen, reinitialize everything
        // display the board, and continue back up to re-run the while(...) loop
        // ...
        if (moveFrom == 'R'){
            cout << endl;
            cout << "   *** Restarting" << endl;
            initializeGame();
            displayBoard();
            continue;
        }

        // Additionally, now also read the piece-to-jump and destination inputs.
        // ...
        cin >> jumpOver;
        jumpOver = toupper(jumpOver);

        cin >> moveTo;
        moveTo = toupper(moveTo);

        // Ensure set of pieces (from, jump, to) are adjacent.  If they aren't, then
        // continue back up to re-run the while(...) loop.
        // ...
        if (!checkAdjacency()) {
            cout << endl << "   *** Pieces must be adjacent. Please retry" << endl << endl;
            continue;
        }

        // Ensure location we're moving FROM has a PlayerPiece in it. If it doesn't, then
        // continue back up to re-run the while(...) loop.
        // ...
        if (!checkMoveFrom()) {
            cout << endl << "   *** Source must have a piece. Please retry" << endl << endl;
            continue;
        }

        // Ensure piece being jumped isn't blank. If it is, then
        // continue back up to re-run the while(...) loop.
        // ...
        if (!checkJumpOver()) {
            cout << endl << "   *** Must jump a piece. Please retry" << endl << endl;
            continue;
        }

        // Ensure location we're moving TO is blank. If it is not, then
        // continue back up to re-run the while(...) loop.
        // ...
        if (!checkMoveTo()) {
            cout << endl << "   *** Destination must be blank. Retry" << endl << endl;
            continue;
        }

        // Make the move and display the board
        // ...
        makeMove();
        displayBoard();
        moveNumber++; // Update the moveNumber variable for next iteration of the loop

    } //end while( numberOfPieces > 1)
    cout << endl;

    // Check for a win
    // ...
    if (numberOfPieces == 1){
        cout << "Congratulations, you did it!" << endl;
    }
    else {
        cout << "Better luck next time." << endl;
    }
    cout << "Done." << endl;
    return 0;
} //end main()

