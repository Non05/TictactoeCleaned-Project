#include "gameManager.h"
#include "gameBoard.h"
#include "ai.h"

#include <stdio.h>

TTT_API int currentPlayer = 1;

// Single-player state is kept here to avoid threading params through every call.
static int singlePlayerMode = 0;
static int aiPlayerId = 2;
static AiDifficulty aiDifficulty = AI_DIFFICULTY_EASY;

// Flush any leftover characters after scanf to keep the next prompt clean.
static void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

void switchPlayer(void) {
    currentPlayer = (currentPlayer == 1) ? 2 : 1;
}

void getPlayerMove(int *row, int *col) {
    int parsed = 0;

    if (row == NULL || col == NULL) {
        return;
    }

    while (!parsed) {
        printf("Player %d, enter row and column (1-3 1-3): ", currentPlayer);

        // Read two integers, reject invalid inputs like letters.
        if (scanf("%d %d", row, col) != 2) {
            printf("Invalid input. Please enter two numbers.\n");
            clearInputBuffer();
            continue;
        }

        clearInputBuffer();
        // Convert 1-based user input to 0-based board indexes.
        *row -= 1;
        *col -= 1;

        if (*row < 0 || *row >= BOARD_SIZE || *col < 0 || *col >= BOARD_SIZE) {
            printf("Move out of bounds. Try again.\n");
            continue;
        }

        if (board[*row][*col] != 0) {
            printf("Cell already occupied. Try again.\n");
            continue;
        }

        // Move is valid.
        parsed = 1;
    }
}

void playerTurn(void) {
    int row = 0;
    int col = 0;

    getPlayerMove(&row, &col);
    placePiece(row, col, currentPlayer);
}

static void aiTurn(void) {
    // Keep AI behavior consistent with human turn flow.
    printf("Computer is making a move...\n");
    aiMove(aiPlayerId, aiDifficulty);
}

void endGame(int state) {
    printBoard();

    if (state == 1 || state == 2) {
        if (singlePlayerMode && state == aiPlayerId) {
            printf("Computer wins!\n");
        } else if (singlePlayerMode) {
            printf("You win!\n");
        } else {
            printf("Player %d wins!\n", state);
        }
    } else if (state == 3) {
        printf("It's a draw!\n");
    }
}

void startGame(void) {
    int state = 0;

    // Multiplayer game always starts with a fresh board and player 1.
    resetBoard();
    currentPlayer = 1;
    singlePlayerMode = 0;

    while (state == 0) {
        printBoard();
        playerTurn();
        state = checkBoardState();
        // Only switch turns while the game is still active.
        if (state == 0) {
            switchPlayer();
        }
    }

    endGame(state);
}

void startSinglePlayerGame(AiDifficulty difficulty) {
    int state = 0;

    resetBoard();
    currentPlayer = 1;

    // By default, human is player 1 and AI is player 2.
    singlePlayerMode = 1;
    aiPlayerId = 2;
    aiDifficulty = difficulty;

    while (state == 0) {
        printBoard();
        if (currentPlayer == aiPlayerId) {
            aiTurn();
        } else {
            playerTurn();
        }

        state = checkBoardState();
        if (state == 0) {
            switchPlayer();
        }
    }

    endGame(state);
}
