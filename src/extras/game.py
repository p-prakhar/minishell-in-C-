# Tic Tac Toe

import random

#Defining the default state of important variables
mark_comp = 'X'
mark_player = 'O'
difficulty = 'medium'
turn = 'random'


def printBoard(board):
    # This function prints out the board that it was passed.
    # "board" is a list of 10 strings representing the board (ignore index 0)
    print(' ' + board[1] + ' | ' + board[2] + ' | ' + board[3])
    print('------------')
    print(' ' + board[4] + ' | ' + board[5] + ' | ' + board[6])
    print('------------')
    print(' ' + board[7] + ' | ' + board[8] + ' | ' + board[9])


# Lets the player type which letter they want to be.
def inputPlayerLetter():
    global mark_player
    global mark_comp

    letter = ''
    while not(letter == 'X' or letter == 'O'):
        print("Do you want to be 'X' or 'O'?")
        letter = input().upper()
    print("\n" * 25)
    if letter == 'X':
        mark_player = 'X'
        mark_comp = 'O'
    else:
        mark_player = 'O'
        mark_comp = 'X'

#To set who would go first
def whoGoesFirst():
    global turn
    print('Do you want to go first? (Yes or No or Random)')
    choice = input().lower()
    print("\n" * 25)
    if choice.startswith('y'):
        turn = 'player'
    elif choice.startswith('r'):
        turn = 'random'
    else:
        turn = 'computer'

#This function is used to set the difficulty level
def difficulty_chooser():
    global difficulty
    print('Do you want to try impossible mode? (Yes or No)')
    choice = input().lower()

    if choice.startswith('y'):
        difficulty = 'impossible'

    else:
        print("\n" * 25)
        print('Do you want to try the easy mode?(Yes sets to easy, No sets to medium)')
        choice = input().lower()
        if choice.startswith('y'):
            difficulty = 'easy'

        else:
            difficulty = 'medium'

    print('\n'*25)
    settings()

# This function returns True if the player wants to play again, otherwise it returns False.
def playAgain():
    print('\nWant to play again? (Yep = new game or Nope = goes to main menu)')
    return input().lower().startswith('y')

#This function makes a move to the desired location
def makeMove(board, letter, move):
    board[move] = letter


def isWinner(board, letter):
    # Given a board and a player's letter, this function returns True if that player has won.
    return ((board[1] == letter and board[2] == letter and board[3] == letter) or
            (board[4] == letter and board[5] == letter and board[6] == letter) or
            (board[7] == letter and board[8] == letter and board[9] == letter) or
            (board[1] == letter and board[4] == letter and board[7] == letter) or
            (board[2] == letter and board[5] == letter and board[8] == letter) or
            (board[3] == letter and board[6] == letter and board[9] == letter) or
            (board[1] == letter and board[5] == letter and board[9] == letter) or
            (board[3] == letter and board[5] == letter and board[7] == letter))


def getBoardCopy(board):
    # Make a duplicate of the board list and return it the duplicate.
    dupBoard = []

    for i in board:
        dupBoard.append(i)

    return dupBoard

# checks if a particular cell is empty
def isSpaceFree(board, move):
    return board[move] == ' '


def getPlayerMove(board):
    # Let the player type in their move.
    move = ''
    while move not in '1 2 3 4 5 6 7 8 9'.split() or not isSpaceFree(board, int(move)):
        print('\nEnter your next move (1-9)')
        move = input()
    return int(move)

#Lets the computer choose a random move
def randomMove(board):
    possibleMoves = []
    for i in range(1,10):
        if isSpaceFree(board, i):
            possibleMoves.append(i)
    if len(possibleMoves) != 0:
        return random.choice(possibleMoves)
    else:
        return None

def chooseRandomMoveFromList(board, movesList):
    # Returns a valid move from the passed list on the passed board.
    # Returns None if there is no valid move.
    possibleMoves = []
    for i in movesList:
        if isSpaceFree(board, i):
            possibleMoves.append(i)

    if len(possibleMoves) != 0:
        return random.choice(possibleMoves)
    else:
        return None


def minimax(board, depth, isMax, alpha, beta, mark_comp):
    # Given a board and the computer's letter, determine where to move and return that move.
    if mark_comp == 'X':
        mark_player = 'O'
    else:
        mark_player = 'X'

    if isWinner(board, mark_comp):
        return 10
    if isWinner(board, mark_player):
        return -10
    if isBoardFull(board):
        return 0

    if isMax:
        best = -1000

        for i in range(1, 10):
            if isSpaceFree(board, i):
                board[i] = mark_comp
                best = max(best, minimax(board, depth+1, not isMax,
                           alpha, beta, mark_comp) - depth)
                alpha = max(alpha, best)
                board[i] = ' '

                if alpha >= beta:
                    break

        return best
    else:
        best = 1000

        for i in range(1, 10):
            if isSpaceFree(board, i):
                board[i] = mark_player
                best = min(best, minimax(board, depth+1, not isMax,
                           alpha, beta, mark_comp) + depth)
                beta = min(beta, best)
                board[i] = ' '

                if alpha >= beta:
                    break

        return best


def findBestMove(board, mark_comp):
    # Given a board and the computer's letter, determine where to move and return that move.
    if mark_comp == 'X':
        mark_player = 'O'
    else:
        mark_player = 'X'

    bestVal = -1000
    bestMove = -1

    for i in range(1, 10):
        if isSpaceFree(board, i):
            board[i] = mark_comp

            moveVal = minimax(board, 0, False, -1000, 1000, mark_comp)

            board[i] = ' '

            if moveVal > bestVal:
                bestMove = i
                bestVal = moveVal

    return bestMove


def isBoardFull(board):
    # Return True if every space on the board has been taken. Otherwise return False.
    for i in range(1, 10):
        if isSpaceFree(board, i):
            return False
    return True

#The settings menu of the tic tac toe game
def settings():
    print('\n Settings')
    print('---------------')
    print('')
    print('Enter the serial number of the setting you want to change')
    print('The settings are in the order of setting name and then the current value\n')
    print('1. Difficulty: ' + difficulty)
    print('2. Marker used for the player: ' + mark_player)
    print('3. Who goes first: ' + turn)
    print('4. Go to the main menu')
    print('5. Start the game with the current settings')
    print('\nEnter the serial number(1-4) of the option you want to choose, choosing an invalid value leads to no action\n')
    choice = ' '
    while choice not in '1 2 3 4 5'.split():
        choice = input()

    if int(choice) == 1:
        print("\n" * 25)
        difficulty_chooser()
        settings()
    elif int(choice) == 2:
        print("\n" * 25)
        inputPlayerLetter()
        settings()
    elif int(choice) == 3:
        print("\n" * 25)
        whoGoesFirst()
        settings()
    elif int(choice) ==  5:
        print("\n" * 25)
        game()
    else:
        print("\n" * 25)
        runMenu()

#The help menu of the game
def help_game():
    print('\n Help')
    print('---------------')
    print('')
    print('\nThis is a text based tic tac toe. You have to enter the index of the cell you want to mark')
    print('Reference of numbering on the board\n')
    printBoard('0 1 2 3 4 5 6 7 8 9'.split())
    print('\nExample: Suppose you enter 5, so the cell in the center (the one labelled 5 here) gets marked')
    print('Difficulty level, who plays first and the mark ( O or X ) assigned to you can be changed in the settings page')
    print('Press enter to go back to the main menu')
    input()
    print("\n" * 25)
    runMenu()

#The credits menu of the game
def credits_game():
    print('\n Credits')
    print('---------------')
    print('')
    print('This game was made by Prakhar Pandey')
    print('Roll Number: 200101081')
    print('Press enter to go back to the main menu')
    input()
    print("\n" * 25)
    runMenu()

#The main menu of the game
def runMenu():
    print('\n Tic Tac Toe')
    print('---------------')
    print('')
    print('1. Play\n2. Settings\n3. Help\n4. Credits\n5. Exit\n')
    print('Enter the serial number(1-5) of the option you want to choose, choosing an invalid value leads to no action\n')
    print('Visit help if this is your first time')
    choice = ' '
    while choice not in '1 2 3 4 5'.split():
        choice = input()

    if int(choice) == 1:
        print("\n" * 25)
        game()
    elif int(choice) == 2:
        print("\n" * 25)
        settings()
    elif int(choice) == 3:
        print("\n" * 25)
        help_game()
    elif int(choice) == 4:
        print("\n" * 25)
        credits_game()
    elif int(choice) == 5:
        exit()
    else:
        print("\n" * 25)
        runMenu()

#The game in its execution
def game():
    global mark_player
    global mark_comp
    global turn
    global difficulty
    if turn == 'random':
        if random.randint(0, 1) == 0:
            turn = 'computer'
        else:
            turn = 'player'
    while True:

        # Reset the board
        currBoard = [' '] * 10
        print('The ' + turn + ' will go first.')
        gameIsPlaying = True

        while gameIsPlaying:
            print('\n')
            if turn == 'player':
                printBoard(currBoard)
                move = getPlayerMove(currBoard)
                makeMove(currBoard, mark_player, move)
                

                if isWinner(currBoard, mark_player):
                    print('\n')
                    printBoard(currBoard)
                    print('\nYayy!!, you won the game')
                    gameIsPlaying = False
                else:
                    if isBoardFull(currBoard):
                        print('\n')
                        printBoard(currBoard)
                        print('\nTough battle! The game is a tie.')
                        break
                    else:
                        turn = 'computer'
            else:
                if difficulty == 'impossible':
                    move = findBestMove(currBoard, mark_comp)
                elif difficulty == 'easy':
                    move = randomMove(currBoard)
                elif difficulty == 'medium':
                    if random.randint(0, 1) == 0:
                        move = findBestMove(currBoard, mark_comp)
                    else:
                        move = randomMove(currBoard)
                
                print('Computer chose: ', move)

                makeMove(currBoard, mark_comp, move)

                if isWinner(currBoard, mark_comp):
                    print('\n')
                    printBoard(currBoard)
                    print('\nYou lose the game. Better luck next time :)')
                    gameIsPlaying = False
                else:
                    if isBoardFull(currBoard):
                        print('\n')
                        printBoard(currBoard)
                        print('\nThe game is a tie. Good game!')
                        break
                    else:
                        turn = 'player'
        if not playAgain():
            print("\n" * 25)
            runMenu()


print("\n" * 25) #clears the screen by printing 25 blank lines first
runMenu()
print('')