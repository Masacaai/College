# Classic Tic-Tac-Toe in Python!
# 
# Author: Aaqel Shaik
# Class: MATH 496
# Version: Python 3.10.5

# Class Board that represents abstraction of the actual gameboard object
class Board(object):

    # We initialize a 2D array with single-spaced strings to represent empty positions
    # We also intialize a boolean to check for the game over state
    def __init__(self):
        self.board = [[" ", " ", " "],
                      [" ", " ", " "],
                      [" ", " ", " "]]
        self.over = False

    # Used for displaying the board
    def displayBoard(self):
        print("\n    A    B    C  ")
        print("  ---------------")
        for i in range(3):
            print(i + 1, end = " ")
            for j in range(3):
                print("|", self.board[i][j], "|", end = "")
            print("\n  ---------------")
        print()
    
    # Used to place a piece on the board
    def placePiece(self, piece, pos):
        # Since the indexing for our array doesn't recognize letters, we need to individually place them
        if pos[1] == "A":
            self.board[int(pos[0])-1][0] = piece
        elif pos[1] == "B":
            self.board[int(pos[0])-1][1] = piece
        elif pos[1] == "C":
            self.board[int(pos[0])-1][2] = piece
    
    # Used to check the board and its status
    def checkStatus(self):
        for i in range(3):
            # Check horizontal win
            if self.board[i][0] == self.board[i][1] == self.board[i][2]!= " ":
                self.over = True
                return self.board[i][0]
            # Check vertical win
            elif self.board[0][i] == self.board[1][i] == self.board[2][i] != " ":
                self.over = True
                return self.board[0][i]
        # Check diagonal wins
        if self.board[0][0] == self.board[1][1] == self.board[2][2] != " ":
            self.over = True
            return self.board[0][0]
        elif self.board[0][2] == self.board[1][1] == self.board[2][0] != " ":
            self.over = True
            return self.board[0][2]
        
        # If empty place is found, return single-spaced string
        for i in range(3):
            for j in range(3):
                if self.board[i][j] == " ":
                    return " "
        # If none of the above conditions are met, it means the game has reached a tie
        self.over = True
        return "tie"
    
    # Used to check empty positions on the board and the next possible moves
    def possibleMoves(self):
        cols = ["A", "B", "C"]
        moves = []
        for i in range(3):
            for j in range(3):
                if self.board[i][j] == " ":
                    moves.append(str(i+1) + cols[j])
        print("There are {} possible moves: ".format(len(moves)), end = " ")
        for a in moves:
            print(a, end = " ")
        print()
        return moves

# A function to handle a player's turn
def playerTurn(board, piece):
    valid = False # This boolena ensures that the game does not progress until the player makes a valid choice
    while not valid:
        moves = board.possibleMoves()
        pos = input("Enter row number followed by column letter to place your piece, or Q to quit: ")
        if pos == "Q":
            board.over = True
            return
        # If positions is not a possible move, prompt again
        if pos not in moves:
            print("Please enter a valid position!\n")
            continue
        else:
            valid = True
        board.placePiece(piece, pos)
        board.displayBoard()
        status = board.checkStatus()
        if status == piece:
            print("Player {} has won!".format(piece))
            print("Game over!")
        elif status == "tie":
            print("It's a tie!")
            print("Game over!")

print("\nWelcome to the classic game of tic-tac-toe, recreated in Python with a TUI!\n")


game = Board()
game.displayBoard()

while not game.over:
    print("Player X's turn:")
    playerTurn(game, "X")
    
    if game.over:
        break

    print("Player O's turn:")
    playerTurn(game, "O")

print("\nGoodbye!\n")