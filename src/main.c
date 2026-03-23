#include <stdio.h>
#include <string.h>

#include "gameManager.h"

#define MAX_INPUT_SIZE 30

int readInput(char *buffer, size_t size);
int madeOfOnlyOneChar(const char *str);
AiDifficulty promptDifficulty(void);

void waitForEnter(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void printMenu() {
    printf("Welcome to Tik-Tac-Toe!\n");
    printf("\t1. Single Player\n");
    printf("\t2. Multiplayer\n");
    printf("\t0. Exit\n");
}

AiDifficulty promptDifficulty(void) {
    char userInput[MAX_INPUT_SIZE];

    while (1) {
        printf("Select difficulty:\n");
        printf("\t1. Easy\n");
        printf("\t2. Hard\n");
        printf("Choice: ");

        if (!readInput(userInput, MAX_INPUT_SIZE)) {
            printf("Invalid input (Out-of-bounds). Try again.\n");
            waitForEnter();
            continue;
        }

        if (!madeOfOnlyOneChar(userInput)) {
            printf("Invalid input (More than one character). Try again.\n");
            waitForEnter();
            continue;
        }

        if (userInput[0] == '1') {
            return AI_DIFFICULTY_EASY;
        }
        if (userInput[0] == '2') {
            return AI_DIFFICULTY_HARD;
        }

        printf("Invalid difficulty. Try again.\n");
        waitForEnter();
    }
}

int readInput(char *buffer, size_t size) {
    if (!fgets(buffer, size, stdin)) {
        return 0;
    }

    size_t len = strlen(buffer);

    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return 0; // input too long
    }

    return 1;
}

int madeOfOnlyOneChar(const char *str) {
    /*
     * Check if the string is empty.
     * Returns true if empty.
     */
    if (str == NULL || str[0] == '\0') {
        return 1;
    }

    // Get the first character of the string
    char firstChar = str[0];

    // Iterate through string, starting from the second character
    for (size_t i = 1; i < strlen(str); i++) {
        // If any character doesn't match first character return false
        if (str[i] != firstChar) {
            return 0;
        }
    }

    // if no other characters found return true
    return 1;
}

int main(void) {
    char userInput[MAX_INPUT_SIZE];
    int validStatus = 0; //1 for true 0 for false

    while (!validStatus) {
        printMenu();
        printf("Make menu selection: ");

        if (!readInput(userInput, MAX_INPUT_SIZE)) {
            printf("Invalid input (Out-of-bounds). Try again.\n");
            waitForEnter();
            continue;
        }

        if (!madeOfOnlyOneChar(userInput)) {
            printf("Invalid input (More than one character). Try again.\n");
            waitForEnter();
            continue;
        }

        switch (userInput[0]) {
            case '1':
                startSinglePlayerGame(promptDifficulty());
                validStatus = 1;
                break;
            case '2':
                startGame();
                validStatus = 1;
                break;
            case '0':
                printf("Exiting...\n");
                validStatus = 1;
                break;
            default:
                printf("Invalid option selected. Try again.\n");
                waitForEnter();
        }
    }

    return 0;
} //end of main
