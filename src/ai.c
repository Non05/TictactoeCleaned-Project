#include "ai.h"
#include "gameBoard.h"

#include <stdlib.h>
#include <time.h>

static void seedRngOnce(void) {
    static int seeded = 0;
    if (!seeded) {
        // Seed only once so easy-mode randomness behaves predictably per run.
        srand((unsigned)time(NULL));
        seeded = 1;
    }
}

static int hasMovesLeft(void) {
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            if (board[row][col] == 0) {
                return 1;
            }
        }
    }
    return 0;
}

static int minimax(int depth, int isMaximizing, int aiPlayer, int humanPlayer) {
    int state = checkBoardState();
    if (state == aiPlayer) {
        // Prefer faster wins for the AI.
        return 10 - depth;
    }
    if (state == humanPlayer) {
        // Prefer slower losses if unavoidable.
        return depth - 10;
    }
    if (state == 3) {
        return 0;
    }

    if (!hasMovesLeft()) {
        return 0;
    }

    if (isMaximizing) {
        int best = -100000;
        for (int row = 0; row < BOARD_SIZE; row++) {
            for (int col = 0; col < BOARD_SIZE; col++) {
                if (board[row][col] != 0) {
                    continue;
                }
                // Try AI move and evaluate the response.
                board[row][col] = aiPlayer;
                int score = minimax(depth + 1, 0, aiPlayer, humanPlayer);
                board[row][col] = 0;
                if (score > best) {
                    best = score;
                }
            }
        }
        return best;
    }

    int best = 100000;
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            if (board[row][col] != 0) {
                continue;
            }
            // Try human move and evaluate the best AI reply.
            board[row][col] = humanPlayer;
            int score = minimax(depth + 1, 1, aiPlayer, humanPlayer);
            board[row][col] = 0;
            if (score < best) {
                best = score;
            }
        }
    }
    return best;
}

static void findRandomMove(int *row, int *col) {
    seedRngOnce();

    // Collect all available cells, then pick uniformly at random.
    int available[BOARD_SIZE * BOARD_SIZE][2];
    int count = 0;

    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            if (board[r][c] == 0) {
                available[count][0] = r;
                available[count][1] = c;
                count++;
            }
        }
    }

    if (count == 0) {
        *row = 0;
        *col = 0;
        return;
    }

    int pick = rand() % count;
    *row = available[pick][0];
    *col = available[pick][1];
}

void findBestMove(int player, AiDifficulty difficulty, int *row, int *col) {
    if (row == NULL || col == NULL) {
        return;
    }

    // Easy mode intentionally ignores optimal play.
    if (difficulty == AI_DIFFICULTY_EASY) {
        findRandomMove(row, col);
        return;
    }

    int aiPlayer = player;
    int humanPlayer = (player == 1) ? 2 : 1;

    int bestScore = -100000;
    int bestRow = 0;
    int bestCol = 0;

    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            if (board[r][c] != 0) {
                continue;
            }

            // Evaluate each possible AI move via minimax.
            board[r][c] = aiPlayer;
            int score = minimax(0, 0, aiPlayer, humanPlayer);
            board[r][c] = 0;

            if (score > bestScore) {
                bestScore = score;
                bestRow = r;
                bestCol = c;
            }
        }
    }

    *row = bestRow;
    *col = bestCol;
}

void aiMove(int player, AiDifficulty difficulty) {
    int row = 0;
    int col = 0;

    findBestMove(player, difficulty, &row, &col);
    placePiece(row, col, player);
}
