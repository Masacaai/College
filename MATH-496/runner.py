import pygame
import sys
import time
import os

from minesweeper import Minesweeper, MinesweeperAI

HEIGHT = 4
WIDTH = 4
MINES = 2

# Colors
BLACK = (0, 0, 0)
GRAY = (180, 180, 180)
WHITE = (255, 255, 255)

# Create game
pygame.init()
size = width, height = 800, 600
screen = pygame.display.set_mode(size)

# Compute relative path
filepath = os.getcwd()

# Fonts
OPEN_SANS = filepath + "/assets/fonts/OpenSans-Regular.ttf"
smallFont = pygame.font.Font(OPEN_SANS, 20)
mediumFont = pygame.font.Font(OPEN_SANS, 28)
largeFont = pygame.font.Font(OPEN_SANS, 40)

# Compute board size
BOARD_PADDING = 20
board_width = ((2 / 3) * 600) - (BOARD_PADDING * 2)
board_height = 400 - (BOARD_PADDING * 2)
cell_size = int(min(board_width / WIDTH, board_height / HEIGHT))
board_origin = (BOARD_PADDING, BOARD_PADDING + 20)


# Add images
flag = pygame.image.load(filepath + "/assets/images/flag.png")
flag = pygame.transform.scale(flag, (cell_size, cell_size))
mine = pygame.image.load(filepath + "/assets/images/mine.png")
mine = pygame.transform.scale(mine, (cell_size, cell_size))

# Create game and AI agent
gameH = Minesweeper(height=HEIGHT, width=WIDTH, mines=MINES)
gameR = gameH
ai = MinesweeperAI(height=HEIGHT, width=WIDTH)

# Keep track of revealed cells, flagged cells, and if a mine was hit
revealed = set()
flags = set()
lost = False

# Open a logfile
if os.path.exists(filepath + "/log.txt"):
    os.remove(filepath + "/log.txt")
log = open("log.txt", "a")

# Set count for number of games played
count = 1

# Set newGame status
newGame = True

# Set buttonClicked status
buttonClicked = False

# Set automate status
automate = False

while True:

        
    if newGame:
        print("Reached newGame if")
        log.write("Game " + str(count) + ":\n")
        newGame = False

    screen.fill(BLACK)
        
    # Draw titles
    titleH = mediumFont.render("Hard-Code", True, WHITE)
    titleR = mediumFont.render("Q-Learning", True, WHITE)
    titleHRect = titleH.get_rect()
    titleRRect = titleR.get_rect()
    titleHRect.center = (200, 20)
    titleRRect.center = (600, 20)
    screen.blit(titleH, titleHRect)
    screen.blit(titleR, titleRRect)

    # Draw board
    cells = []
    for i in range(HEIGHT):
        row = []
        for j in range(WIDTH):

            # Draw rectangle for cell
            rectH = pygame.Rect(
                board_origin[0] + j * cell_size,
                board_origin[1] + i * cell_size,
                cell_size, cell_size
            )
            rectR = pygame.Rect(
                420 + j * cell_size,
                board_origin[1] + i * cell_size,
                cell_size, cell_size
            )
            pygame.draw.rect(screen, GRAY, rectH)
            pygame.draw.rect(screen, WHITE, rectH, 3)
            pygame.draw.rect(screen, GRAY, rectR)
            pygame.draw.rect(screen, WHITE, rectR, 3)

            # Add a mine, flag, or number if needed
            if gameH.is_mine((i, j)) and lost:
                screen.blit(mine, rectH)
            elif (i, j) in flags:
                screen.blit(flag, rectH)
            elif (i, j) in revealed:
                neighbors = largeFont.render(
                    str(gameH.nearby_mines((i, j))),
                    True, BLACK
                )
                neighborsTextRect = neighbors.get_rect()
                neighborsTextRect.center = rectH.center
                screen.blit(neighbors, neighborsTextRect)

            row.append(rectH)
        cells.append(row)

    # AI Move button
    aiButton = pygame.Rect(
        BOARD_PADDING, (5 / 6) * height,
        (width / 3) - BOARD_PADDING * 2, 50
    )
    buttonText = mediumFont.render("AI Move", True, BLACK)
    buttonRect = buttonText.get_rect()
    buttonRect.center = aiButton.center
    pygame.draw.rect(screen, WHITE, aiButton)
    screen.blit(buttonText, buttonRect)

    # Reset button
    resetButton = pygame.Rect(
        (width / 3), (5 / 6) * height,
        (width / 3) - BOARD_PADDING * 2, 50
    )
    buttonText = mediumFont.render("Reset", True, BLACK)
    buttonRect = buttonText.get_rect()
    buttonRect.center = resetButton.center
    pygame.draw.rect(screen, WHITE, resetButton)
    screen.blit(buttonText, buttonRect)
    
    # Automate button
    autoButton = pygame.Rect(
        (2 / 3) * width - BOARD_PADDING, (5 / 6) * height,
        (width / 3) - BOARD_PADDING * 2, 50
    )
    buttonText = mediumFont.render("Automate", True, BLACK)
    buttonRect = buttonText.get_rect()
    buttonRect.center = autoButton.center
    pygame.draw.rect(screen, WHITE, autoButton)
    screen.blit(buttonText, buttonRect)

    # Display text
    text = "Lost" if lost else "Won" if gameH.mines == flags else ""
    text = mediumFont.render(text, True, WHITE)
    textRect = text.get_rect()
    textRect.center = (2 * BOARD_PADDING + 10, (3 / 4) * height)
    screen.blit(text, textRect)

    move = None

    # Check if game quit
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            log.close()
            sys.exit()
        elif event.type == pygame.MOUSEBUTTONDOWN:
            if event.button == 1:

                # If AI button clicked, make an AI move
                if  aiButton.collidepoint(event.pos) and not lost:
                    buttonClicked = True      

                # Reset game state
                elif resetButton.collidepoint(event.pos):
                    gameH = Minesweeper(height=HEIGHT, width=WIDTH, mines=MINES)
                    ai = MinesweeperAI(height=HEIGHT, width=WIDTH)
                    revealed = set()
                    flags = set()
                    lost = False
                    newGame = True
                    count += 1
                    continue
        
                # Automate game
                elif autoButton.collidepoint(event.pos) and gameH.mines != flags and not lost:
                    automate = True
    
    # Perform AI move if needed
    if automate or buttonClicked:
        move = ai.make_safe_move()
        if move is None:
            move = ai.make_random_move()
            if move is None:
                flags = ai.mines.copy()
                print("No moves left to make.")
                automate = False
            else:
                print("No known safe moves, AI making random move.")
        else:
            print("AI making safe move.")
            time.sleep(0.2)
        buttonClicked = False

    # Make move and update AI knowledge
    if move:
        if gameH.is_mine(move):
            lost = True
            automate = False
        else:
            nearby = gameH.nearby_mines(move)
            revealed.add(move)
            ai.add_knowledge(move, nearby)

    pygame.display.flip()
