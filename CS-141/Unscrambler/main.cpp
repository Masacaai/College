/* ---------------------------------------------
    Program 5: Unscrambler
        Create a board that is filled with words
        which are then scrambled and presented to
        the user, who rotates the rows and columns
        to try and get the original words displayed
        in the right order on the board.

    Course: CS 141, Fall 2021. Tues 9 AM lab
    System: Fedora 34 using JetBrains CLion
    Author: Mohammed Aaqel Shaik Abdul Mazeed
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <cassert>
using namespace std;

class Board{
public:

    // Display board ( connected string passed as argument)
    void display(string boardString){

        // The display function prints different sentences depending on
        // whether the string being displayed is scrambled or not
        if (scrambledBoard != unscrambledBoard){ // If board is solved, don't print anything here
            if (boardString == scrambledBoard){ // If the passed argument is a scrambled string
                cout << "These are the words that you should try to spell out using the board, in order: " << endl;

                // This part of the code finds the index of the last non-whitespace character in the string
                long unsigned int lastIndex;
                for (int i = unscrambledBoard.size() - 1; i >= 0; --i){
                    if( unscrambledBoard.at(i) != ' '){
                        lastIndex = i;
                        break;
                    }
                }

                // This part of the code separates the connected string and displays them with commas and periods
                for (long unsigned int i = 0; i < unscrambledBoard.size(); ++i){
                    if (i == lastIndex){ // If we are at the end, add a period and break out of the loop
                        cout << unscrambledBoard.at(i) << ".";
                        break;
                    }
                    else if (unscrambledBoard.at(i) == ' '){ // If we encounter a whitespace, print a comma and a space
                        cout << ", ";
                    }
                    else { // If we encounter a normal character, just print it
                        cout << unscrambledBoard.at(i);
                    }
                }

                cout << endl << "Current board:" << endl;
            }
            else { // If the passed argument is the unscrambled string
                cout << "The completed board should look like:" << endl;
            }
        }

        // This part of the code displays the code in the expected format
        cout << "      ";                       // The random whitespaces here are done just to format the code
        for (int i = 0; i < boardSize; ++i){    // the way it is shown in Zybooks (they are non-essential)
            cout << " " << i << " ";
        }
        cout << endl;
        cout << "      ";
        for (int i = 0; i < boardSize * 4 - 1; ++i){ // Print dashes
            cout << "-";
        }
        cout << endl;

        for (int i = 0; i < boardSize; ++i){ // Print characters on board with pipes
            cout << "   " << i << " |";

            for (int j = i * boardSize; j < i * boardSize + boardSize; ++j){
                cout << " " << boardString.at(j) << " " << "|";
            }
            cout << endl;
            cout << "      ";
            for (int i = 0; i < boardSize * 4 - 1; ++i){ // Print dashes
                cout << "-";
            }
            cout << endl;
        }
        cout << "Current board words: " << boardString << endl;

    } // end display()

    // Rotate row ( the row number, the number of positions to rotate)
    void rotateRow(int rowNumber, int numOfPositions){
        if ( numOfPositions > 0){ // If number of positions is positive, then we shift all the characters to the right.
            for (int i = 0; i < numOfPositions; ++i){
                // First get the index of the right-most square on this row
                int lastIndex = (rowNumber + 1) * boardSize - 1;
                // Store the right-most character
                char lastChar = scrambledBoard.at( lastIndex);
                // Shift characters to the right, starting with the last one
                int j;
                for( j = lastIndex; j > lastIndex - boardSize + 1; j--) {
                    // Store left neighbor on top of the current one
                    scrambledBoard.at(j) = scrambledBoard.at(j-1);
                }
                // Put the old last character into place on the far left
                scrambledBoard.at(j) = lastChar;
            }
        }
        else{ // If number of positions is negative, then we shift all the characters to the left.
            for (int i = numOfPositions; i < 0; ++i){
                // First get the index of the left-most square on this row
                int firstIndex = rowNumber * boardSize;
                // Store the left-most character
                char firstChar = scrambledBoard.at( firstIndex);
                // Shift characters to the left, starting with the first one
                int j;
                for( j = firstIndex; j < firstIndex + boardSize - 1; ++j) {
                    // Store right neighbor on top of the current one
                    scrambledBoard.at(j) = scrambledBoard.at(j+1);
                }
                // Put the old first character into place on the far right
                scrambledBoard.at(j) = firstChar;
            }
        }
    } // end rotateRow()

    // Rotate column ( the column number, the number of positions to rotate)
    void rotateColumn(int columnNumber, int numOfPositions){
        if ( numOfPositions > 0){ // If number of positions is positive, then we shift all the characters downward.
            for (int i = 0; i < numOfPositions; ++i){
                // First get the index of the bottom square on this row
                int lastIndex = columnNumber + boardSize * (boardSize - 1);
                // Store the bottom character
                char lastChar = scrambledBoard.at( lastIndex);
                // Shift characters down, starting with the last one
                int j;
                for( j = lastIndex; j>lastIndex - boardSize * (boardSize - 1); j -= boardSize) {
                    // Store top neighbor on top of the current one
                    scrambledBoard.at(j) = scrambledBoard.at(j-boardSize);
                }
                // Put the old last character into place on the far top
                scrambledBoard.at(j) = lastChar;
            }
        }
        else{ // If number of positions is negative, then we shift all the characters upward.
            for (int i = numOfPositions; i < 0; ++i){
                // First get the index of the top square on this row
                int firstIndex = columnNumber;
                // Store the top character
                char firstChar = scrambledBoard.at( firstIndex);
                // Shift characters up, starting with the first one
                int j;
                for( j = firstIndex; j < firstIndex + boardSize * (boardSize-1); j += boardSize) {
                    // Store bottom neighbor on top of the current one
                    scrambledBoard.at(j) = scrambledBoard.at(j+boardSize);
                }
                // Put the old first character into place on the far bottom
                scrambledBoard.at(j) = firstChar;
            }
        }
    } // end rotateColumn

    // Getter functions
    string getScrambled(){return scrambledBoard;}
    string getUnscrambled(){return unscrambledBoard;}
    int getBoardSize(){return boardSize;}

    // Setter functions
    void setScrambled(string scrambledBoard){Board::scrambledBoard = scrambledBoard;}
    void setUnscrambled(string unscrambledBoard){Board::unscrambledBoard = unscrambledBoard;}
    void setBoardSize(int boardSize){Board::boardSize = boardSize;}

private:
    string scrambledBoard; // String to store scrambled connected string
    string unscrambledBoard; // String to store unscrambled (solved) connected string
    int boardSize; // Size of board

}; // end of Board class

// Read words from dictionary-3to5-letters.txt into a vector
// (Vector to be updated with dictionary words is passed as parameter)
void readFromDictionary( vector <string> & vect)
{
    // Read into vector
    ifstream inStream;                      // Declare an input stream for reading
    inStream.open( "dictionary-3to5-letters.txt");       // Open file
    assert( inStream.fail() == false );     // Ensure file open worked

    // Clear the vector in case it is used previously.
    vect.clear();

    // Keep repeating while input from the file yields a word
    string newWord;                         // Store a single input word
    while( inStream >> newWord) {           // While there is another word to be read
        // Add this new word to the end of the vector, growing it in the process
        vect.push_back( newWord);
    }

    // Close the dictionary file
    inStream.close();
} // end readFromDictionary()

// Create the board (Board to be updated with values, vector that holds previous board states,
//                   size of board, number of times to scramble the board)
void createBoard(Board & board, vector <Board> & boardStates, int boardSize, int numberOfScrambles){
    vector <string> dictionary; // Vector to store dictionary words
    boardStates.clear(); // Clear vector in case it is not empty
    string boardWords; // String to store connected words
    readFromDictionary(dictionary);

    long unsigned int lengthLeft = (boardSize * boardSize); // Variable to store space left on the board
    while (true){
        int a = rand() % dictionary.size();
        if ( dictionary.at(a).size() > lengthLeft){ // If the length of the selected word is more than
            continue;                               // the space left on the board, continue with the loop
        }
        boardWords += dictionary.at(a); // Add word to connected string
        lengthLeft -= dictionary.at(a).size() + 1; // Subtract length left based on length of word
        if ((boardSize*boardSize) - boardWords.size() <= 3){ // If there are 3 or less spaces left on board
            int length = boardWords.size(); // Store the length of the connected string
            for (int i = 0; i < ((boardSize * boardSize) - length); ++i){
                boardWords += " "; // Add spaces to the end of the connected
            }                      // string depending on how much space is left
            break; // Break out of loop if board is filled
        }
        else {
            boardWords += " "; // If there are more than three spaces left
        }                      // on board, just add a single space and continue
    }

    board.setBoardSize(boardSize);
    board.setUnscrambled(boardWords);
    board.setScrambled(boardWords);
    for (int i = 0; i < numberOfScrambles; ++i){ // Scramble board based on user input
        board.rotateRow(rand() % boardSize, 1);
        board.rotateColumn(rand() % boardSize, 1);
    }
    board.display(board.getScrambled());
    boardStates.push_back(board); // Add board state to the vector
} // end createBoard()

// Rotate rows and columns (Board to be updated with values, vector that holds previous board states)
void rotate(Board & board, vector <Board> & boardStates){
    char choice;
    int position; // Row or Column number
    int numberOfMoves; // Number of positions to rotate row or column
    bool valid = false; // Bool variable that checks for invalid inputs
    while (!valid){
        cout << "Enter the row/column you would like to rotate, and the number of positions to rotate by." << endl
             << "This should be in the format of <R or C> <row/column number> <number of positions to rotate>," << endl
             << "where valid row and column numbers are between 0 and " << board.getBoardSize() - 1 << "," << endl
             << "E.g. R 0 1 would rotate the top row (row 0) of the board to the right once," << endl
             << "c 1 -2 would rotate the second column (col 1) of the board upwards twice." << endl
             << "Your choice: ";
        cin >> choice
            >> position
            >> numberOfMoves;
        choice = toupper(choice);
        if ((choice != 'C') & (choice != 'R')){
            cout << "First input must be 'R' or 'C'. Try again." << endl;
            continue;
        }
        // If row or column number is not in between 0 and boardSize - 1
        if ((position < 0) || ( position > board.getBoardSize() - 1)){
            cout << "Number must be between 0 and " << board.getBoardSize() - 1 << ". Try again." << endl;
            continue;
        }
        if (choice == 'C'){
            board.rotateColumn(position,numberOfMoves);
            valid = true;
        }
        if (choice == 'R') {
            board.rotateRow(position, numberOfMoves);
            valid = true;
        }
    }
    boardStates.push_back(board); // Add the new board state to the vector of board states
} // end rotate()


int main() {
    srand(1);
    char choice; // Choice between different options
    bool boardIsCreated = false; // Bool variable to differentiate between the two different usecases of 'B'
    int boardSize = 0; // Size of the board
    int numberOfScrambles = 0; // Number of times to scramble the board
    Board gameBoard; // Board is declared here to facilitate easier access to it from other functions
    vector <Board> gameStates; // Vector that holds all the previous board states

    cout << "Program 5: Unscrambler" << endl
         << "CS 141, Fall 2021, UIC" << endl << endl
         << "You will be presented with a board that is filled with scrambled words. Rotate the rows and columns" << endl
         << "to get the words displayed in the right order." << endl << endl
         << "13893 words have been read in from the dictionary." << endl << endl
         << "Enter Q to quit or B to begin: ";
    cin >> choice;
    choice = toupper(choice);

    while(choice != 'Q'){
        if (choice == 'B'){
            if (boardIsCreated){ // If board has already been created, reset the board
                // Reset the board by setting the scrambled string to the earliest version in the vector
                gameBoard.setScrambled(gameStates.at(0).getScrambled());
                gameBoard.display(gameBoard.getScrambled());
            }
            else { // If board hasn't been created yet, create the board
                while (boardSize < 4){
                    cout << "Choose your board size (must be a number greater than or equal to 4): ";
                    cin >> boardSize;
                    if (boardSize < 4){ cout << "The board size must be at least 4. Retry." << endl;}
                }
                while (numberOfScrambles < 1){
                    cout << "Choose the number of times you would like the board to be scrambled (must be a single number >= 1): ";
                    cin >> numberOfScrambles;
                    if (numberOfScrambles < 1){ cout << "The number of times you select must be at least 1. Retry." << endl;}
                }
                createBoard(gameBoard, gameStates, boardSize, numberOfScrambles);
                boardIsCreated = true;

            }
        }
        if(choice == 'R'){ // Rotate rows and columns
            rotate(gameBoard, gameStates);
            gameBoard.display(gameBoard.getScrambled());
        }
        if(choice == 'C'){ // Show the completed board
            gameBoard.display(gameBoard.getUnscrambled());
            gameBoard.display(gameBoard.getScrambled());
        }
        if(choice == 'G'){ // Generate a new board with same size and number of scrambles
            createBoard(gameBoard, gameStates, boardSize, numberOfScrambles);}

        if (gameBoard.getUnscrambled() == gameBoard.getScrambled()){ // If the player has solved the board
            cout << "Congratulations, you won! ";
            break;
        }
        cout << "Enter one of the following:" << endl
             << "   R to rotate a row or column," << endl
             << "   C to view what the completed board should look like," << endl
             << "   B to reset the board back to the beginning," << endl
             << "   G to generate a new board with new random words," << endl
             << "   S to have the computer automatically solve a board that you enter (5 points extra credit)," << endl
             << "   Q to quit." << endl
             << "Your choice: ";
        cin >> choice;
        choice = toupper(choice);
    }
    cout << "Thank you for playing!" << endl
         << "Exiting program..." << endl;

    return 0;
}
