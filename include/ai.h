#ifndef AI_H
#define AI_H

#include "tictactoe_api.h"

typedef enum {
    AI_DIFFICULTY_EASY = 0,
    AI_DIFFICULTY_HARD = 1
} AiDifficulty;

// Makes a move for the AI player
TTT_API void aiMove(int player, AiDifficulty difficulty);

// Finds the best move for the AI
TTT_API void findBestMove(int player, AiDifficulty difficulty, int *row, int *col);

#endif
