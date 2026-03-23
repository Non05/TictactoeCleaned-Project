#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "tictactoe_api.h"
#include "ai.h"

// Current player (1 = X, 2 = O)
TTT_API extern int currentPlayer;

// Starts and runs the game loop
TTT_API void startGame(void);

// Starts and runs a single-player game (human = player 1, AI = player 2)
TTT_API void startSinglePlayerGame(AiDifficulty difficulty);

// Switches between players
TTT_API void switchPlayer(void);

// Handles a player's turn
TTT_API void playerTurn(void);

// Prompts user for move input
TTT_API void getPlayerMove(int *row, int *col);

// Ends the game and prints the result
TTT_API void endGame(int state);

#endif // GAMEMANAGER_H
