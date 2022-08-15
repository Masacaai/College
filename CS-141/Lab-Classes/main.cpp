#include <iostream>
#include <vector>

using namespace std;


class Board{
public:
    Board(string boardCharacters = "_________"){ Board::boardCharacters = boardCharacters;}

    void displayBoard(){
        cout << "Board is: \n";

        // Display board position index values
        for( int i=0; i<boardCharacters.size(); i++) {
            cout << i << " ";
            // Display a newline character at the end of each row
            if( (i+1)%3 == 0) {
                cout << endl;
            }
        }
        cout << endl;

        // Display board characters
        for( int i=0; i<boardCharacters.size(); i++) {
            cout << boardCharacters.at( i) << " ";
            // Display a newline character at the end of each row
            if( (i+1)%3 == 0) {
                cout << endl;
            }
        }
        cout << endl;
    }

    void makeMove(int & moveNumber, int movePosition, char pieceToPlace){
        // Prompt for user input and make move

        cout << moveNumber << ". Enter square to play: ";
        cin >> movePosition;
        pieceToPlace = 'X';
        // Set pieceToPlay to 'O' for even moves
        if( moveNumber % 2 == 0) {
            pieceToPlace = 'O';
        }
        boardCharacters.at( movePosition) = pieceToPlace;

        // Increment the move number
        moveNumber++;
    }
private:
    string boardCharacters;

};


//-----------------------------------------------------------
int main() {
    cout << "Lab 13: TacTacToe using Classes \n"
         << endl;
    int moveNumber = 1;     // Move number starts at 1
    int theSquare = 0;      // Square into which to play, in range 1..9
    char pieceToPlay = ' '; // Should be 'X' or 'O' for each move
    Board gameBoard;
    vector <Board> listOfBoards;

    // Game play loop
    while( true) {
        gameBoard.displayBoard();
        listOfBoards.push_back(gameBoard);
        gameBoard.makeMove(moveNumber,theSquare,pieceToPlay);

        // Exit game if board is full
        if( moveNumber == 10) {
            // Display the final board
            gameBoard.displayBoard();
            cout << "State of play: " << endl;
            for (int i = 0; i < listOfBoards.size(); ++i){
                listOfBoards.at(i).displayBoard();
            }
            break;  // Break out of gameplay loop
        }
    } //end while( true)

    cout << "Game over." << endl;

    return 0;
} //end main()

